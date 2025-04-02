#include "Renderer/Vulkan/VulkanRenderer.h"
#include <SDL3/SDL_vulkan.h>

#define NUM_SAMPLES VK_SAMPLE_COUNT_1_BIT


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
    
    error = InitSwapchainExtension(v_info, s_engine);
    if(!Throw::Check(error)) {
        return error;
    }   

    error = InitDevice(v_info);
    if(!Throw::Check(error)) {
        return error;
    }   

    // CREATE DEPTH BUFFER
    VkImageCreateInfo image_info = {};
    const VkFormat depth_format = VK_FORMAT_D16_UNORM;
    VkFormatProperties props;
    vkGetPhysicalDeviceFormatProperties(v_info.gpus[0], depth_format, &props);
    if(props.linearTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT){
        image_info.tiling = VK_IMAGE_TILING_LINEAR;
    } else if(props.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT){
        image_info.tiling = VK_IMAGE_TILING_OPTIMAL;
    } else {
        return Throw::ExitError("VK_FORMAT_D16_UNIFORM unsuported on this gpu.");
    }

    image_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    image_info.pNext = NULL;
    image_info.imageType = VK_IMAGE_TYPE_2D;
    image_info.format  = depth_format;
    image_info.extent.width = info->getWidth();
    image_info.extent.height = info->getHeight();
    image_info.extent.depth = 1;
    // add a slider (if minecraft has this we should)
    image_info.mipLevels = 1;
    image_info.arrayLayers = 1;
    image_info.samples = NUM_SAMPLES;
    image_info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    image_info.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
    image_info.queueFamilyIndexCount = 0;
    image_info.pQueueFamilyIndices = NULL;
    image_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    image_info.flags = 0;

    VkMemoryAllocateInfo mem_alloc = {};
    mem_alloc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    mem_alloc.pNext = NULL;
    mem_alloc.allocationSize = 0;
    mem_alloc.memoryTypeIndex = 0;

    VkImageViewCreateInfo view_info = {};
    view_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    view_info.pNext = NULL;
    view_info.image = VK_NULL_HANDLE;
    view_info.format = depth_format;
    view_info.components.r = VK_COMPONENT_SWIZZLE_R;
    view_info.components.g = VK_COMPONENT_SWIZZLE_G;
    view_info.components.b = VK_COMPONENT_SWIZZLE_B;
    view_info.components.a = VK_COMPONENT_SWIZZLE_A;
    view_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
    view_info.subresourceRange.baseMipLevel = 0;
    view_info.subresourceRange.levelCount = 1;
    view_info.subresourceRange.baseArrayLayer = 0;
    view_info.subresourceRange.layerCount = 1;
    view_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
    view_info.flags = 0;

    VkMemoryRequirements mem_reqs;

    v_info.depth.format = depth_format;

    VkResult result = vkCreateImage(v_info.device, &image_info, NULL, &v_info.depth.image);
    if(result != VK_SUCCESS) return VkResultToThrow(result, exit_error);

    vkGetImageMemoryRequirements(v_info.device, v_info.depth.image, &mem_reqs);

    mem_alloc.allocationSize = mem_reqs.size;

    bool pass = memory_type_from_properties(v_info, mem_reqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, &mem_alloc.memoryTypeIndex);
    if(!pass) return Throw::ExitError("Could Not Identity Memory Properties");

    result = vkAllocateMemory(v_info.device, &mem_alloc, NULL, &v_info.depth.mem);
    if(result != VK_SUCCESS) return Throw::ExitError("Could Not Allocate Memory for Depth Buffer");

    result = vkBindImageMemory(v_info.device, v_info.depth.image, v_info.depth.mem, 0);
    if(result != VK_SUCCESS) return Throw::ExitError("Could Not Bind Image Memory");

    view_info.image = v_info.depth.image;
    result = vkCreateImageView(v_info.device, &view_info, NULL, &v_info.depth.view);
    if(result != VK_SUCCESS) return Throw::ExitError("Could Not Create Image View");

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





