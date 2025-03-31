#include "Renderer/Vulkan/VulkanRenderer.h"
#include <SDL3/SDL_vulkan.h>




VulkanRenderer::VulkanRenderer(FirestarEngine* engine) {
    v_info.engine = engine;
    s_engine = engine;
}

VulkanRenderer::~VulkanRenderer() {

}

Throw* VulkanRenderer::Initialise(GameInfo* info) {
    v_info.game_info = info;
    Throw* error = nullptr;

    error = InitGlobalLayerProperties(v_info);
    if(!Throw::Check(error)){
        return error;
    }

    InitIntanceExtensionNames(v_info);
    InitDeviceExtensionNames(v_info);

    
    error = InitInstance(v_info, *info);
    if(!Throw::Check(error)) {
        return error;
    }

    error = InitEnumerateDevice(v_info, 0);
    if(!Throw::Check(error)) {
        return error;
    }
    


    s_engine->getMainWindow()->CreateWindow(*info, Vulkan);
    

    FSE_Window* window = s_engine->getMainWindow()->getWindow();
    // NEEDS TO BE REPLACED WHEN I WANT TO DITCH SDL 3
    if(SDL_Vulkan_CreateSurface(window->window, v_info.instance, NULL, &v_info.surface)){
        return Throw::ExitError("SDL Failed to Create Vulkan Surface");
    }

    // MEMOERY MANAGMENT WOO WHOO LETS GOOOO
    VkBool32 *pSupportsPresent = (VkBool32 *) malloc(v_info.queue_family_count * sizeof(VkBool32));

    for(uint32_t i = 0; i < v_info.queue_family_count; i++){
        // UPDATE TO SUPPORT GPU SWITCHING
        vkGetPhysicalDeviceSurfaceSupportKHR(v_info.gpus[0], i, v_info.surface, &pSupportsPresent[i]);
    }

    v_info.graphics_queue_family_index = UINT32_MAX;
    v_info.present_queue_family_index = UINT32_MAX;
    for(uint32_t i = 0; i < v_info.queue_family_count; i++){
        if((v_info.queue_props[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0){
            if(v_info.graphics_queue_family_index == UINT32_MAX) v_info.graphics_queue_family_index = i;

            if(pSupportsPresent[i] == VK_TRUE){
                v_info.graphics_queue_family_index = i;
                v_info.present_queue_family_index = i;
                break;
            }
        }
    }

    if(v_info.present_queue_family_index == UINT32_MAX) {
        for(size_t i = 0; i < v_info.queue_family_count; i++){
            if(pSupportsPresent[i] == VK_TRUE){
                v_info.present_queue_family_index = i;
                break;
            }
        }
    }

    // NO DONT GOOOOOOOO
    free(pSupportsPresent);

    if(v_info.graphics_queue_family_index == UINT32_MAX || v_info.present_queue_family_index == UINT32_MAX){
        return Throw::ExitError("Could not find Queues for Grapcis and Presents :(", -1);
    }

    error = InitDevice(v_info);
    if(!Throw::Check(error)) {
        return error;
    }

    uint32_t formatCount;
    // .... im just going to keep the selecting the first gpu **FACEPALM**
    VkResult res = vkGetPhysicalDeviceSurfaceFormatsKHR(v_info.gpus[0], v_info.surface, &formatCount, NULL);
    if(res != VK_SUCCESS) return VkResultToThrow(res, exit_error);
    // LETS MALLOC AGAIN WOO 
    VkSurfaceFormatKHR * surfFormats = (VkSurfaceFormatKHR *) malloc(formatCount* sizeof(VkSurfaceFormatKHR));
    // .. do i even need to write this (probably)
    res = vkGetPhysicalDeviceSurfaceFormatsKHR(v_info.gpus[0], v_info.surface, &formatCount, surfFormats);
    if(res != VK_SUCCESS) return VkResultToThrow(res, exit_error);

    if(formatCount == 1 && surfFormats[0].format == VK_FORMAT_UNDEFINED){
        v_info.format = VK_FORMAT_B8G8R8A8_UNORM;
    }else{
        if(formatCount < 1) return Throw::ExitError("Were not going to make it no were not going to make it were not going to make it anymore", -1);
        v_info.format = surfFormats[0].format;
    }

    // eh
    free(surfFormats);

    VkSurfaceCapabilitiesKHR surfaceCap;

    // THE LIST OF FIXES GROWS
    res = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(v_info.gpus[0], v_info.surface, &surfaceCap);
    if(res != VK_SUCCESS) return VkResultToThrow(res, exit_error);

    uint32_t presentModeCount;
    // AHHAHAHAHAHAH more gpu issues
    res = vkGetPhysicalDeviceSurfacePresentModesKHR(v_info.gpus[0], v_info.surface, &presentModeCount, NULL);
    if(res != VK_SUCCESS) return VkResultToThrow(res, exit_error);

    VkPresentModeKHR *presentModes = (VkPresentModeKHR *)malloc(presentModeCount * sizeof(VkPresentModeKHR));

    res = vkGetPhysicalDeviceSurfacePresentModesKHR(v_info.gpus[0], v_info.surface, &presentModeCount, presentModes);
    if(res != VK_SUCCESS) return VkResultToThrow(res, exit_error);

    VkExtent2D swapchainExtent;

    if(surfaceCap.currentExtent.width == 0xFFFFFFFF){
        swapchainExtent.width = v_info.game_info->getWidth();
        swapchainExtent.height = v_info.game_info->getHeight();

        if(swapchainExtent.width < surfaceCap.minImageExtent.width){
            swapchainExtent.width = surfaceCap.minImageExtent.width;
        } else if(swapchainExtent.width > surfaceCap.maxImageExtent.width){
            swapchainExtent.width = surfaceCap.maxImageExtent.width;
        }

        if(swapchainExtent.height < surfaceCap.minImageExtent.height){
            swapchainExtent.height = surfaceCap.minImageExtent.height;
        } else if(swapchainExtent.height > surfaceCap.maxImageExtent.height){
            swapchainExtent.height = surfaceCap.maxImageExtent.height;
        }
        
    } else {
        swapchainExtent = surfaceCap.currentExtent;
    }

    // WTH IS A FIFO
    VkPresentModeKHR swapchainPresentMode = VK_PRESENT_MODE_FIFO_KHR;

    uint32_t desireNumberofSwapChainImages = surfaceCap.minImageCount;

    VkSurfaceTransformFlagBitsKHR preTransform;
    if(surfaceCap.supportedTransforms & VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR){
        preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    }else {
        preTransform = surfaceCap.currentTransform;
    }

    VkCompositeAlphaFlagBitsKHR compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    VkCompositeAlphaFlagBitsKHR compositeAlphaFlags[4] = {
        VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
        VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR,
        VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR,
        VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR,
    };

    for(uint32_t i = 0; i > sizeof(compositeAlphaFlags)/ sizeof(compositeAlphaFlags[0]); i++){
        if(surfaceCap.supportedCompositeAlpha & compositeAlphaFlags[i]){
            compositeAlpha = compositeAlphaFlags[i];
            break;
        }
    }

    VkSwapchainCreateInfoKHR swapchain_ci = {};
    swapchain_ci.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    swapchain_ci.pNext = NULL;
    swapchain_ci.surface = v_info.surface;
    swapchain_ci.minImageCount = desireNumberofSwapChainImages;
    swapchain_ci.imageFormat = v_info.format;
    swapchain_ci.imageExtent.width = swapchainExtent.width;
    swapchain_ci.imageExtent.height = swapchainExtent.height;
    swapchain_ci.preTransform = preTransform;
    swapchain_ci.compositeAlpha = compositeAlpha;
    swapchain_ci.presentMode = swapchainPresentMode;
    swapchain_ci.oldSwapchain = VK_NULL_HANDLE;
    swapchain_ci.clipped = true;
    swapchain_ci.imageColorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;
    swapchain_ci.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    swapchain_ci.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    swapchain_ci.queueFamilyIndexCount = 0;
    swapchain_ci.pQueueFamilyIndices = NULL;
    uint32_t queueFamilyIndice[2] = {(uint32_t) v_info.graphics_queue_family_index, (uint32_t)v_info.present_queue_family_index};
    if(v_info.graphics_queue_family_index != v_info.present_queue_family_index){
        swapchain_ci.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        swapchain_ci.queueFamilyIndexCount = 2;
        swapchain_ci.pQueueFamilyIndices = queueFamilyIndice;
    }

    res = vkCreateSwapchainKHR(v_info.device, &swapchain_ci, NULL, &v_info.swap_chain);
    if(res != VK_SUCCESS) return VkResultToThrow(res, exit_error);

    res = vkGetSwapchainImagesKHR(v_info.device, v_info.swap_chain, &v_info.swapchain_image_count, NULL);
    if(res != VK_SUCCESS) return VkResultToThrow(res, exit_error);

    VkImage * swapchainImages = (VkImage*)malloc(v_info.swapchain_image_count * sizeof(VkImage));

    res = vkGetSwapchainImagesKHR(v_info.device, v_info.swap_chain, &v_info.swapchain_image_count, swapchainImages);
    if(res != VK_SUCCESS) return VkResultToThrow(res, exit_error);

    v_info.buffers.resize(v_info.swapchain_image_count);
    for(uint32_t i = 0; i < v_info.swapchain_image_count; i++){
        v_info.buffers[i].image = swapchainImages[i];
    }

    // NO NOT MY SWAPCHAIN IT COST SO MUCH 
    free(swapchainImages);

    for(uint32_t i = 0; i < v_info.swapchain_image_count; i++){
        VkImageViewCreateInfo colour_image_view = {};
        colour_image_view.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        colour_image_view.pNext = NULL;
        colour_image_view.flags = 0;
        colour_image_view.image = v_info.buffers[i].image;
        colour_image_view.viewType = VK_IMAGE_VIEW_TYPE_2D;
        colour_image_view.format = v_info.format;
        colour_image_view.components.r = VK_COMPONENT_SWIZZLE_R;
        colour_image_view.components.g = VK_COMPONENT_SWIZZLE_G;
        colour_image_view.components.b = VK_COMPONENT_SWIZZLE_B;
        colour_image_view.components.a = VK_COMPONENT_SWIZZLE_A;
        colour_image_view.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        colour_image_view.subresourceRange.baseMipLevel = 0;
        colour_image_view.subresourceRange.levelCount = 1;
        colour_image_view.subresourceRange.baseArrayLayer = 0;
        colour_image_view.subresourceRange.layerCount = 1;

        res = vkCreateImageView(v_info.device, &colour_image_view, NULL, &v_info.buffers[i].view);
        if(res != VK_SUCCESS) return VkResultToThrow(res, exit_error);
    }
    return nullptr;
}

void VulkanRenderer::Draw() {

}

void VulkanRenderer::Clear() {

}

void VulkanRenderer::Shutdown() {
    for(uint32_t i = 0; i < v_info.swapchain_image_count; i++){
        vkDestroyImageView(v_info.device, v_info.buffers[i].view, NULL);
    }

    

    vkDestroyInstance(v_info.instance, NULL);
}

std::string VulkanRenderer::GetError() {
    return v_error;
}



