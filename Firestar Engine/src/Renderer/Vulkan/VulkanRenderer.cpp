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
    
    error = InitSwapchainExtension(v_info, s_engine);
    if(!Throw::Check(error)) {
        return error;
    }   

    error = InitDevice(v_info);
    if(!Throw::Check(error)) {
        return error;
    }   

    error = InitCommandPool(v_info);
    if(!Throw::Check(error)) {
        return error;
    }   

    error = InitCommandBuffer(v_info);
    if(!Throw::Check(error)) {
        return error;
    }   

    error = ExecuteBeginCommandBuffer(v_info);
    if(!Throw::Check(error)) {
        return error;
    } 

    InitDeviceQueue(v_info);

    error = InitSwapchain(v_info, 0);
    if(!Throw::Check(error)) {
        return error;
    } 

    error = InitDepthBuffer(v_info);
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
    for(uint32_t i = 0; i < v_info.swapchain_image_count; i++){
        vkDestroyImageView(v_info.device, v_info.buffers[i].view, NULL);
    }

    

    vkDestroyInstance(v_info.instance, NULL);
}

std::string VulkanRenderer::GetError() {
    return v_error;
}





