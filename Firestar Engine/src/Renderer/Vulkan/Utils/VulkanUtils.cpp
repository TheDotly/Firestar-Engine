#include "Renderer/Vulkan/Utils/VulkanUtils.h"

Throw* VkResultToThrow(VkResult result, ErrorLevel level){
    switch (result)
    {
        case VK_SUCCESS: return nullptr;
        case VK_NOT_READY: return Throw::DynamicThrow("Vulkan Not Ready", level);
        case VK_TIMEOUT: return Throw::DynamicThrow("Vulkan Timed Out", level);
        case VK_EVENT_SET: return Throw::DynamicThrow("Vulkan Event Set", level);
        case VK_EVENT_RESET: return Throw::DynamicThrow("Vulkan Event Reset", level);
        case VK_INCOMPLETE: return Throw::DynamicThrow("Vulkan Not Ready or Incomplete", level);
        case VK_ERROR_OUT_OF_HOST_MEMORY: return Throw::DynamicThrow("Host Ran Out of Memory", level);
        case VK_ERROR_OUT_OF_DEVICE_MEMORY: return Throw::DynamicThrow("Vulkan Device is Out of Memory", level);
        case VK_ERROR_INITIALIZATION_FAILED: return Throw::DynamicThrow("Vulkan Failed to Initalise", level);
        case VK_ERROR_DEVICE_LOST: return Throw::DynamicThrow("Vulkan Device Lost or Unpluged", level);
        case VK_ERROR_MEMORY_MAP_FAILED: return Throw::DynamicThrow("Vulkan Failed to Get or Create the Memory Map", level);
        case VK_ERROR_LAYER_NOT_PRESENT: return Throw::DynamicThrow("Vulkan Layer Not Found", level);
        case VK_ERROR_EXTENSION_NOT_PRESENT: return Throw::DynamicThrow("Vulkan Extention Missing", level);
        case VK_ERROR_FEATURE_NOT_PRESENT: return Throw::DynamicThrow("Vulkan Computer Doesnt Support Feature", level);
        case VK_ERROR_INCOMPATIBLE_DRIVER: return Throw::DynamicThrow("Vulkan Driver Installed is Incompatable", level);
        case VK_ERROR_TOO_MANY_OBJECTS: return Throw::DynamicThrow("Vulkan TOO MANY OBJECTS", level);
        case VK_ERROR_FORMAT_NOT_SUPPORTED: return Throw::DynamicThrow("Vulkan Format Not Supported", level);
        case VK_ERROR_FRAGMENTED_POOL: return Throw::DynamicThrow("Vulkan Fragmented Pool Error", level);
        case VK_ERROR_UNKNOWN: return Throw::DynamicThrow("Vulkan Threw an Unknow Error", level);
        case VK_ERROR_OUT_OF_POOL_MEMORY: return Throw::DynamicThrow("Vulkan Pool Ran Out of Memory :(", level);
        case VK_ERROR_INVALID_EXTERNAL_HANDLE: return Throw::DynamicThrow("Vulkan Invalid External Handle", level);
        case VK_ERROR_FRAGMENTATION: return Throw::DynamicThrow("Vulkan Framentation Error", level);
        case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS: return Throw::DynamicThrow("Vulkan Invalid Opaque Capture Address", level);
        case VK_PIPELINE_COMPILE_REQUIRED: return Throw::DynamicThrow("Vulkan Pipeline Needs to Be Compiled", level);
        case VK_ERROR_SURFACE_LOST_KHR: return Throw::DynamicThrow("Vulkan Surface Lost", level);
        default: return Throw::DynamicThrow("Unkown Error", level);
    }

    return nullptr;
}

Throw* InitGlobalExtentionProperties(LayerProperties &layer_props){
    VkExtensionProperties *instance_extentions;
    uint32_t instance_extentions_count;
    VkResult result;
    char *layer_name = NULL;

    layer_name = layer_props.properties.layerName;

    do{
        result = vkEnumerateInstanceExtensionProperties(layer_name, &instance_extentions_count, NULL);
        if(result) return VkResultToThrow(result, ErrorLevel::exit_error);

        if(instance_extentions_count == 0){
            return nullptr;
        }

        layer_props.instance_extentions.resize(instance_extentions_count);

        instance_extentions = layer_props.instance_extentions.data();
        result = vkEnumerateInstanceExtensionProperties(layer_name, &instance_extentions_count, instance_extentions);
    
    } while (result == VK_INCOMPLETE);
    
    return VkResultToThrow(result, ErrorLevel::exit_error);
}


Throw* InitGlobalLayerProperties(VulkanInfo &info) {
    uint32_t instance_layer_count;
    VkLayerProperties *vk_props = NULL;

    VkResult result;

    // add android support if i want?

    do {
        result = vkEnumerateInstanceLayerProperties(&instance_layer_count, NULL);
        if(result) return VkResultToThrow(result, ErrorLevel::exit_error);

        if(instance_layer_count == 0){
            return nullptr;
        }

        vk_props = (VkLayerProperties *)realloc(vk_props, instance_layer_count * sizeof(VkLayerProperties));

        result = vkEnumerateInstanceLayerProperties(&instance_layer_count, vk_props);
    } while (result == VK_INCOMPLETE);
    
    for (uint32_t i = 0; i < instance_layer_count; i++){
        LayerProperties layer_props;
        layer_props.properties = vk_props[i];
        Throw* error = InitGlobalExtentionProperties(layer_props);
        if(error != nullptr) return error;
        info.instance_layer_props.push_back(layer_props);
    }

    // FREE MY MAN HE DID NOTHING WRONG
    free(vk_props);
    // thank you :)

    return VkResultToThrow(result, ErrorLevel::exit_error);
}

Throw* InitInstance(VulkanInfo &info, GameInfo game){
    VkApplicationInfo app_info = {};
    app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_info.pNext = NULL;
    app_info.pApplicationName = game.getTitle().c_str();
    app_info.applicationVersion = 1;
    app_info.pEngineName = "FireStar Engine";
    app_info.engineVersion = 1; 
    app_info.apiVersion = VK_API_VERSION_1_3;

    VkInstanceCreateInfo inst_info = {};
    inst_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    inst_info.pNext = NULL;
    inst_info.flags = 0;
    inst_info.pApplicationInfo = &app_info;
    inst_info.enabledLayerCount = info.instance_extention_names.size();
    inst_info.ppEnabledExtensionNames = info.instance_layer_names.size() ? info.instance_layer_names.data() : NULL;
    inst_info.enabledExtensionCount = info.instance_extention_names.size();
    inst_info.ppEnabledExtensionNames = info.instance_extention_names.data();

    VkResult result = vkCreateInstance(&inst_info, NULL, &info.instance);
    if(result){
        return VkResultToThrow(result, ErrorLevel::exit_error);
    }

    return nullptr;
}

Throw* InitDeviceExtensionProperties(VulkanInfo &info, LayerProperties &layer_props){
    VkExtensionProperties *device_extensions;
    uint32_t device_extension_count;
    VkResult res;
    char *layer_name = NULL;

    layer_name = layer_props.properties.layerName;

    do {
        // TODO: NEED TO UPDATE TO SUPPORT GPU SELECT
        res = vkEnumerateDeviceExtensionProperties(info.gpus[0], layer_name, &device_extension_count, NULL);

        if(res) return VkResultToThrow(res, exit_error);

        if(device_extension_count == 0){
            return nullptr;
        }

        layer_props.device_extentions.resize(device_extension_count);
        device_extensions = layer_props.device_extentions.data();
        // TODO: NEED TO ADD SUPPORT FOR GPU SELECT
        res = vkEnumerateDeviceExtensionProperties(info.gpus[0], layer_name, &device_extension_count, device_extensions);
    } while (res == VK_INCOMPLETE);
   
    return VkResultToThrow(res, exit_error);
}

Throw* InitEnumerateDevice(VulkanInfo &info, uint32_t gpu_count){
    uint32_t const req_count = gpu_count;
    VkResult result = vkEnumeratePhysicalDevices(info.instance, &gpu_count, NULL);

    if(result){
        return VkResultToThrow(result, exit_error);
    }

    info.gpus.resize(gpu_count);

    result = vkEnumeratePhysicalDevices(info.instance, &gpu_count, info.gpus.data());
    if(result){
        return VkResultToThrow(result, exit_error);
    }

    // UPDATE THIS SO USER CAN SELECT MAIN GPU 
    vkGetPhysicalDeviceQueueFamilyProperties(info.gpus[0], &info.queue_family_count, NULL);

    if(!(info.queue_family_count >= 1)){
        return Throw::ExitError("The GPU has to Little buffers");
    }

    // GPU SELECTION NEEDS TO BE ADDED LATER
    vkGetPhysicalDeviceMemoryProperties(info.gpus[0], &info.memory_props);
    vkGetPhysicalDeviceProperties(info.gpus[0], &info.gpu_props);

    for(auto &layer_props : info.instance_layer_props){
        Throw * error = InitDeviceExtensionProperties(info, layer_props);
        if(error != nullptr){
            return error;
        }
    }

    return VkResultToThrow(result, exit_error);
}


Throw* InitQueueFamilyIndex(VulkanInfo &info){

    // FIX FOR SELECTABLE GPU
    vkGetPhysicalDeviceQueueFamilyProperties(info.gpus[0], &info.queue_family_count, NULL);
    if(info.queue_family_count < 1){
        return Throw::ExitError("Family Queue is To Small");
    }

    info.queue_props.resize(info.queue_family_count);
    vkGetPhysicalDeviceQueueFamilyProperties(info.gpus[0], &info.queue_family_count, info.queue_props.data());
    if(info.queue_family_count < 1){
        return Throw::ExitError("Family Queue is To Small");
    }

    bool found = false;
    for(unsigned int i = 0; i < info.queue_family_count; i++){
        if(info.queue_props[i].queueFlags & VK_QUEUE_GRAPHICS_BIT){
            info.graphics_queue_family_index = i;
            found = true;
            break;
        }
    }

    if(!found){
        return Throw::ExitError("The Graphics Queue never existed");
    }
    
    return nullptr;
}

Throw* InitDevice(VulkanInfo &info){
    VkResult res;
    VkDeviceQueueCreateInfo queue_info = {};

    float queue_priorities[1] = {0.0};
    queue_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queue_info.pNext = NULL;
    queue_info.queueCount = 1;
    queue_info.pQueuePriorities = queue_priorities;
    queue_info.queueFamilyIndex = info.graphics_queue_family_index;

    VkDeviceCreateInfo device_info = {};
    device_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    device_info.pNext = NULL;
    device_info.queueCreateInfoCount = 1;
    device_info.pQueueCreateInfos = &queue_info;
    device_info.enabledExtensionCount = info.device_extension_names.size();
    device_info.ppEnabledExtensionNames = device_info.enabledExtensionCount ? info.device_extension_names.data() : NULL;
    device_info.pEnabledFeatures = NULL;

    res = vkCreateDevice(info.gpus[0], &device_info, NULL, &info.device);
    if(res){
        return Throw::ExitError("Failed to Create Device");
    }

    return VkResultToThrow(res, exit_error);
}

void InitIntanceExtensionNames(VulkanInfo &info){
    info.instance_extention_names.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
}

void InitDeviceExtensionNames(VulkanInfo &info){
    info.device_extension_names.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
}

Throw* InitSwapchainExtension(VulkanInfo &info){
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