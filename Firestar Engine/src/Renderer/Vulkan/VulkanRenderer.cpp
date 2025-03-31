#include "Renderer/Vulkan/VulkanRenderer.h"





VulkanRenderer::VulkanRenderer(FirestarEngine* engine) {
    s_engine = engine;
}

VulkanRenderer::~VulkanRenderer() {

}

Throw* VulkanRenderer::Initialise(GameInfo* info) {

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

    /*error = InitQueueFamilyIndex(v_info);
    if(!Throw::Check(error)) {
        return error;
    }

    error = InitDevice(v_info);
    if(!Throw::Check(error)) {
        return error;
    }*/

    
























































    
    s_engine->getMainWindow()->CreateWindow(*info, Vulkan);

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



