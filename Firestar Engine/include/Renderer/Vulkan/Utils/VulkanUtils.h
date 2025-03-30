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



#define CMD_TIMEOUT 1000000

struct vulkaninfo {
    VkInstance instance;
    std::vector<VkPhysicalDevice> gpus;
    VkDevice device;

    //Layer Information
    std::vector<const char *> instance_layer_names;
    std::vector<const char *> instance_extention_names;
    std::vector<LayerProperties> instance_layer_props;
    std::vector<VkExtensionProperties> instance_extention_props;

};

typedef struct vulkaninfo VulkanInfo;

typedef struct {
    VkLayerProperties properties;
    std::vector<VkExtensionProperties> instance_extentions;
    std::vector<VkExtensionProperties> device_extentions;
} LayerProperties;

// Init Helper Functions
Throw* InitGlobalExtentionProperties(LayerProperties &layer_props);

Throw* InitGlobalLayerProperties(VulkanInfo &info);

Throw* InitInstance(VulkanInfo &info, GameInfo game);

Throw* InitEnumerateDevice(VulkanInfo &info);

Throw* VkResultToThrow(VkResult result, ErrorLevel level);