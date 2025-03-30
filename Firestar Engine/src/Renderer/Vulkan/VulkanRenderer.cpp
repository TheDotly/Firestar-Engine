#include "Renderer/Vulkan/VulkanRenderer.h"

// Extra Local Functions




VulkanRenderer::VulkanRenderer() {

}

VulkanRenderer::~VulkanRenderer() {

}

Throw* VulkanRenderer::Initialise(GameInfo* info) {

    Throw* error = nullptr;

    error = InitGlobalLayerProperties(v_info);
    if(!Throw::Check(error)){
        return error;
    }

    
    error = InitInstance(v_info, *info);
    if(!Throw::Check(error)) {
        return error;
    }

    error = InitEnumerateDevice(v_info, 0);
    if(!Throw::Check(error)) {
        return error;
    }

    error = InitQueueFamilyIndex(v_info);
    if(!Throw::Check(error)) {
        return error;
    }

    error = InitDevice(v_info);
    if(!Throw::Check(error)) {
        return error;
    }

    

    return nullptr;
}

void VulkanRenderer::Draw() {

}

void VulkanRenderer::Clear() {

}

void VulkanRenderer::Shutdown() {
    vkDestroyInstance(v_info.instance, NULL);
}

std::string VulkanRenderer::GetError() {
    return v_error;
}



