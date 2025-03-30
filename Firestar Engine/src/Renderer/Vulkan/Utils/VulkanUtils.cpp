#include "Vulkan/Utils/VulkanUtils.h"

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

Throw* InitEnumerateDevice(VulkanInfo &info){

}
