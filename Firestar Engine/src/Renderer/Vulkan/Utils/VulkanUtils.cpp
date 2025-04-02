#include "Renderer/Vulkan/Utils/VulkanUtils.h"
#include <SDL3/SDL_vulkan.h>


#define NUM_SAMPLES VK_SAMPLE_COUNT_1_BIT

#define NUM_VIEWPORTS 1
#define NUM_SCISSORS NUM_VIEWPORTS

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

Throw* InitSwapchainExtension(VulkanInfo &info, FirestarEngine* engine){
    Throw* error = nullptr;
    FSE_Window* window = engine->getMainWindow()->getWindow();
    // NEEDS TO BE REPLACED WHEN I WANT TO DITCH SDL 3
    if(SDL_Vulkan_CreateSurface(window->window, info.instance, NULL, &info.surface)){
        return Throw::ExitError("SDL Failed to Create Vulkan Surface");
    }

    // MEMOERY MANAGMENT WOO WHOO LETS GOOOO
    VkBool32 *pSupportsPresent = (VkBool32 *) malloc(info.queue_family_count * sizeof(VkBool32));

    for(uint32_t i = 0; i < info.queue_family_count; i++){
        // UPDATE TO SUPPORT GPU SWITCHING
        vkGetPhysicalDeviceSurfaceSupportKHR(info.gpus[0], i, info.surface, &pSupportsPresent[i]);
    }

    info.graphics_queue_family_index = UINT32_MAX;
    info.present_queue_family_index = UINT32_MAX;
    for(uint32_t i = 0; i < info.queue_family_count; i++){
        if((info.queue_props[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0){
            if(info.graphics_queue_family_index == UINT32_MAX) info.graphics_queue_family_index = i;

            if(pSupportsPresent[i] == VK_TRUE){
                info.graphics_queue_family_index = i;
                info.present_queue_family_index = i;
                break;
            }
        }
    }

    if(info.present_queue_family_index == UINT32_MAX) {
        for(size_t i = 0; i < info.queue_family_count; i++){
            if(pSupportsPresent[i] == VK_TRUE){
                info.present_queue_family_index = i;
                break;
            }
        }
    }

    // NO DONT GOOOOOOOO
    free(pSupportsPresent);

    if(info.graphics_queue_family_index == UINT32_MAX || info.present_queue_family_index == UINT32_MAX){
        return Throw::ExitError("Could not find Queues for Grapcis and Presents :(", -1);
    }

    error = InitDevice(info);
    if(!Throw::Check(error)) {
        return error;
    }

    uint32_t formatCount;
    // .... im just going to keep the selecting the first gpu **FACEPALM**
    VkResult res = vkGetPhysicalDeviceSurfaceFormatsKHR(info.gpus[0], info.surface, &formatCount, NULL);
    if(res != VK_SUCCESS) return VkResultToThrow(res, exit_error);
    // LETS MALLOC AGAIN WOO 
    VkSurfaceFormatKHR * surfFormats = (VkSurfaceFormatKHR *) malloc(formatCount* sizeof(VkSurfaceFormatKHR));
    // .. do i even need to write this (probably)
    res = vkGetPhysicalDeviceSurfaceFormatsKHR(info.gpus[0], info.surface, &formatCount, surfFormats);
    if(res != VK_SUCCESS) return VkResultToThrow(res, exit_error);

   if(formatCount < 1) return Throw::ExitError("Failed to Create Swapchain Extentions Formatcount to small");
}

bool memory_type_from_properties(VulkanInfo &info, uint32_t typeBits, VkFlags requirements_mask, uint32_t *typeIndex){
    for (uint32_t i = 0; i < info.memory_props.memoryTypeCount; i++) {
        if ((typeBits & 1) == 1) {
            // Type is available, does it match user properties?
            if ((info.memory_props.memoryTypes[i].propertyFlags & requirements_mask) == requirements_mask) {
                *typeIndex = i;
                return true;
            }
        }
        typeBits >>= 1;
    }
    // No memory types matched, return failure
    return false;
}

Throw* InitCommandPool(VulkanInfo &info){
    VkResult res;

    VkCommandPoolCreateInfo cmd_pool_info = {};
    cmd_pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    cmd_pool_info.pNext = NULL;
    cmd_pool_info.queueFamilyIndex = info.graphics_queue_family_index;
    cmd_pool_info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

    res = vkCreateCommandPool(info.device, &cmd_pool_info, NULL, &info.cmd_pool);

    return VkResultToThrow(res, exit_error);
}

Throw* InitCommandBuffer(VulkanInfo &info){
     VkResult res;

     VkCommandBufferAllocateInfo cmd = {};
     cmd.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
     cmd.pNext = NULL;
     cmd.commandPool = info.cmd_pool;
     cmd.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
     cmd.commandBufferCount = 1;

     res =vkAllocateCommandBuffers(info.device, &cmd, &info.cmd);

     return VkResultToThrow(res, exit_error);
}

Throw* ExecuteBeginCommandBuffer(VulkanInfo &info){
    VkResult res;

    VkCommandBufferBeginInfo cmd_buf_info = {};
    cmd_buf_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    cmd_buf_info.pNext = NULL;
    cmd_buf_info.flags = 0;
    cmd_buf_info.pInheritanceInfo = NULL;

    res = vkBeginCommandBuffer(info.cmd, &cmd_buf_info);

    return VkResultToThrow(res, exit_error);
}

void InitDeviceQueue(VulkanInfo &info){
    vkGetDeviceQueue(info.device, info.graphics_queue_family_index, 0 , &info.graphics_queue);

    if(info.graphics_queue_family_index == info.present_queue_family_index){
        info.present_queue = info.graphics_queue;
    }else{
        vkGetDeviceQueue(info.device, info.present_queue_family_index, 0, &info.present_queue);
    }
}

Throw* InitSwapchain(VulkanInfo &info, VkImageUsageFlags usageFlags) {
    VkResult res;
    VkSurfaceCapabilitiesKHR surfCap;

    // Add Support for GPU Selection
    res = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(info.gpus[0], info.surface, &surfCap);
    if(res){
        return VkResultToThrow(res, exit_error);
    }

    uint32_t presentModeCount;
    res = vkGetPhysicalDeviceSurfacePresentModesKHR(info.gpus[0], info.surface , &presentModeCount, NULL);
    if(res){
        return VkResultToThrow(res, exit_error);
    }

    VkPresentModeKHR *presentModes = (VkPresentModeKHR *)malloc(presentModeCount * sizeof(VkPresentModeKHR));

    if(presentModes){
        return Throw::ExitError("Failed to Create PresentModes");
    }

    res = vkGetPhysicalDeviceSurfacePresentModesKHR(info.gpus[0], info.surface , &presentModeCount, presentModes);
    if(res){
        return VkResultToThrow(res, exit_error);
    }

    VkExtent2D swapchainExtent; 

    if(surfCap.currentExtent.width == 0xFFFFFFFF){
        swapchainExtent.width = info.game_info->getWidth();
        swapchainExtent.height = info.game_info->getHeight();
        
        if(swapchainExtent.width < surfCap.minImageExtent.width){
            swapchainExtent.width = surfCap.minImageExtent.width;
        }else if(swapchainExtent.width > surfCap.maxImageExtent.width){
            swapchainExtent.width = surfCap.maxImageExtent.width;
        }

        if(swapchainExtent.height < surfCap.minImageExtent.height){
            swapchainExtent.height = surfCap.minImageExtent.height;
        }else if(swapchainExtent.height > surfCap.maxImageExtent.height){
            swapchainExtent.height = surfCap.maxImageExtent.height;
        }
    }else {
        swapchainExtent = surfCap.currentExtent;
    }

    VkPresentModeKHR swpachainPresentMode = VK_PRESENT_MODE_FIFO_KHR;

    uint32_t desiredNumberOfSwapChainImages = surfCap.minImageCount;

    VkSurfaceTransformFlagBitsKHR preTransform;
    if(surfCap.supportedTransforms & VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR) {
        preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    }else {
        preTransform = surfCap.currentTransform;
    }

    VkCompositeAlphaFlagBitsKHR compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    VkCompositeAlphaFlagBitsKHR compositeAlphaFlags[4] = {
        VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
        VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR,
        VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR,
        VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR,
    };

    for (uint32_t i = 0; i < sizeof(compositeAlphaFlags) / sizeof(compositeAlphaFlags[0]); i++) {
        if (surfCap.supportedCompositeAlpha & compositeAlphaFlags[i]) {
            compositeAlpha = compositeAlphaFlags[i];
            break;
        }
    }

    VkSwapchainCreateInfoKHR swapchain_ci = {};
    swapchain_ci.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    swapchain_ci.pNext = NULL;
    swapchain_ci.surface = info.surface;
    swapchain_ci.minImageCount = desiredNumberOfSwapChainImages;
    swapchain_ci.imageFormat = info.format;
    swapchain_ci.imageExtent.width = swapchainExtent.width;
    swapchain_ci.imageExtent.width = swapchainExtent.width;
    swapchain_ci.preTransform = preTransform;
    swapchain_ci.compositeAlpha = compositeAlpha;
    swapchain_ci.imageArrayLayers = 1;
    swapchain_ci.presentMode = swpachainPresentMode;
    swapchain_ci.oldSwapchain = VK_NULL_HANDLE;
    swapchain_ci.clipped = false;
    swapchain_ci.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
    swapchain_ci.imageUsage = usageFlags;
    swapchain_ci.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    swapchain_ci.queueFamilyIndexCount = 0;
    swapchain_ci.pQueueFamilyIndices = NULL;
    uint32_t queueFamilyIndices[2] = {(uint32_t)info.graphics_queue_family_index, (uint32_t)info.present_queue_family_index};
    if (info.graphics_queue_family_index != info.present_queue_family_index) {
        swapchain_ci.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        swapchain_ci.queueFamilyIndexCount = 2;
        swapchain_ci.pQueueFamilyIndices = queueFamilyIndices;
    }

    res = vkCreateSwapchainKHR(info.device, &swapchain_ci, NULL, &info.swap_chain);
    if(res){
        return VkResultToThrow(res, exit_error);
    }

    res = vkGetSwapchainImagesKHR(info.device, info.swap_chain, &info.swapchain_image_count, NULL);
    if(res){
        return VkResultToThrow(res, exit_error);
    }

    VkImage *swapchainImages  = (VkImage *)malloc(info.swapchain_image_count * sizeof(VkImage));
    if(swapchainImages){
        return Throw::ExitError("Could Not Create Swapchain Images Malloc Failed");
    }

    res = vkGetSwapchainImagesKHR(info.device, info.swap_chain, &info.swapchain_image_count, swapchainImages);
    if(res){
        return VkResultToThrow(res, exit_error);
    }

    for(uint32_t i = 0; i < info.swapchain_image_count; i++){
        SwapChainBuffer sc_buffer;

        VkImageViewCreateInfo colour_image_view = {};
        colour_image_view.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        colour_image_view.pNext = NULL;
        colour_image_view.format = info.format;
        colour_image_view.components.r = VK_COMPONENT_SWIZZLE_R;
        colour_image_view.components.g = VK_COMPONENT_SWIZZLE_G;
        colour_image_view.components.b = VK_COMPONENT_SWIZZLE_B;
        colour_image_view.components.a = VK_COMPONENT_SWIZZLE_A;
        colour_image_view.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        colour_image_view.subresourceRange.baseMipLevel = 0;
        colour_image_view.subresourceRange.levelCount = 1;
        colour_image_view.subresourceRange.baseArrayLayer = 0;
        colour_image_view.subresourceRange.layerCount = 1;
        colour_image_view.viewType = VK_IMAGE_VIEW_TYPE_2D;
        colour_image_view.flags = 0;

        sc_buffer.image = swapchainImages[i];

        colour_image_view.image = sc_buffer.image;

        res = vkCreateImageView(info.device, &colour_image_view, NULL, &sc_buffer.view);
        info.buffers.push_back(sc_buffer);
        if(res){
            return VkResultToThrow(res, exit_error);
        }
    }

    free(swapchainImages);
    info.current_buffer = 0;

    if(NULL != presentModes){
        free(presentModes);
    }

    return nullptr;
}

Throw* InitDepthBuffer(VulkanInfo &info){
    VkResult res;
    bool pass;
    VkImageCreateInfo image_info = {};
    VkFormatProperties props;

    if (info.depth.format == VK_FORMAT_UNDEFINED) info.depth.format = VK_FORMAT_D16_UNORM;

    const VkFormat depth_format = info.depth.format;
    vkGetPhysicalDeviceFormatProperties(info.gpus[0], depth_format, &props);

    if (props.linearTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) {
        image_info.tiling = VK_IMAGE_TILING_LINEAR;
    } else if (props.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) {
        image_info.tiling = VK_IMAGE_TILING_OPTIMAL;
    } else {
        return Throw::ExitError("depth Format Unsupproted");
    }

    image_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    image_info.pNext = NULL;
    image_info.imageType = VK_IMAGE_TYPE_2D;
    image_info.format = depth_format;
    image_info.extent.width = info.game_info->getWidth();
    image_info.extent.height = info.game_info->getHeight();
    image_info.extent.depth = 1;
    image_info.mipLevels = 1;
    image_info.arrayLayers = 1;
    image_info.samples = NUM_SAMPLES;
    image_info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    image_info.queueFamilyIndexCount = 0;
    image_info.pQueueFamilyIndices = NULL;
    image_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    image_info.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
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

    if (depth_format == VK_FORMAT_D16_UNORM_S8_UINT || depth_format == VK_FORMAT_D24_UNORM_S8_UINT ||
        depth_format == VK_FORMAT_D32_SFLOAT_S8_UINT) {
        view_info.subresourceRange.aspectMask |= VK_IMAGE_ASPECT_STENCIL_BIT;
    }

    VkMemoryRequirements mem_reqs;

    /* Create image */
    res = vkCreateImage(info.device, &image_info, NULL, &info.depth.image);
    if(res){
        return VkResultToThrow(res, exit_error);
    }

    vkGetImageMemoryRequirements(info.device, info.depth.image, &mem_reqs);

    mem_alloc.allocationSize = mem_reqs.size;
    /* Use the memory properties to determine the type of memory required */
    pass =
        memory_type_from_properties(info, mem_reqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, &mem_alloc.memoryTypeIndex);
        if(pass){
            return Throw::ExitError("Failed to Get Memory Type From Properties");
        }

    /* Allocate memory */
    res = vkAllocateMemory(info.device, &mem_alloc, NULL, &info.depth.mem);
    if(res){
        return VkResultToThrow(res, exit_error);
    }

    /* Bind memory */
    res = vkBindImageMemory(info.device, info.depth.image, info.depth.mem, 0);
    if(res){
        return VkResultToThrow(res, exit_error);
    }

    /* Create image view */
    view_info.image = info.depth.image;
    res = vkCreateImageView(info.device, &view_info, NULL, &info.depth.view);
    if(res){
        return VkResultToThrow(res, exit_error);
    }

    return nullptr;
}