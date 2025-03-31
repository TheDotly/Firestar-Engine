#pragma once

/*
    Joshua Gessner 2025
    Vulkan Helper Functions

    based on https://github.com/LunarG/VulkanSamples/blob/master/API-Samples/utils/util.hpp
*/

#include <vector>
#include <string>
#include "DataTypes/GameInfo.h"
#include "DataTypes/Throw.h"

#include <vulkan/vulkan.h>
#include "FirestarEngine.h"


#define CMD_TIMEOUT 1000000

typedef struct {
    VkLayerProperties properties;
    std::vector<VkExtensionProperties> instance_extentions;
    std::vector<VkExtensionProperties> device_extentions;
} LayerProperties;

typedef struct {
    VkImage image;
    VkImageView view;
} SwapChainBuffer;

typedef struct {
    FirestarEngine * engine;
    VkInstance instance;
    std::vector<VkPhysicalDevice> gpus;
    VkDevice device;

    //Layer Information
    std::vector<const char *> instance_layer_names;
    std::vector<const char *> instance_extention_names;
    std::vector<LayerProperties> instance_layer_props;
    std::vector<VkExtensionProperties> instance_extention_props;

    uint32_t queue_family_count;
    uint32_t current_buffer;

    std::vector<const char*> device_extension_names;
    std::vector<VkExtensionProperties> device_extension_properties;
    uint32_t graphics_queue_family_index;
    uint32_t present_queue_family_index;
    VkPhysicalDeviceProperties gpu_props;
    std::vector<VkQueueFamilyProperties> queue_props;

    VkSurfaceKHR surface;

    //Frame
    VkFramebuffer *framebuffers;
    GameInfo * game_info;
    VkFormat format;

    //Swap Frame
    uint32_t swapchain_image_count;
    VkSwapchainKHR swap_chain;
    std::vector<SwapChainBuffer> buffers;
    VkSemaphore ImageAcquiredSemaphore;

    //Memory
    VkPhysicalDeviceMemoryProperties memory_props;

} VulkanInfo;




// Init Helper Functions
Throw* InitGlobalExtentionProperties(LayerProperties &layer_props);

Throw* InitGlobalLayerProperties(VulkanInfo &info);

Throw* InitInstance(VulkanInfo &info, GameInfo game);

Throw* InitEnumerateDevice(VulkanInfo &info, uint32_t gpu_count);

Throw* VkResultToThrow(VkResult result, ErrorLevel level);

Throw* InitDeviceExtensionProperties(VulkanInfo &info, LayerProperties &layer_props);

// THIS MAY BE OBSOLETE DO NOT USE UNLESS TESTING 
// RENDERPIPELING
Throw* InitQueueFamilyIndex(VulkanInfo &info);

Throw* InitDevice(VulkanInfo &info);

void InitIntanceExtensionNames(VulkanInfo &info);
void InitDeviceExtensionNames(VulkanInfo &info);

Throw* InitSwapchainExtension(VulkanInfo &info);