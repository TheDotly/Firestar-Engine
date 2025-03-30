#include "Renderer/Vulkan/VulkanRenderer.h"

// Extra Local Functions




VulkanRenderer::VulkanRenderer() {

}

VulkanRenderer::~VulkanRenderer() {

}

Throw* VulkanRenderer::Initialise(GameInfo* info) {
    Throw* error = nullptr;

    error = InitGlobalLayerProperties(v_info);
    if(Throw::Check(error)){
        return error;
    }

    
    error = InitInstance(v_info, *info);
    if(Throw::Check(error)) {
        return error;
    }


    VkResult res;
    uint32_t gpu_count = 1;
    res = vkEnumeratePhysicalDevices(v_info.instance, &gpu_count, NULL);
    if(res) {
        error = Throw::ExitError("GPU not Found do you have one installed", -1);
        return error;
    }

    v_info.gpus.resize(gpu_count);
    res = vkEnumeratePhysicalDevices(v_info.instance, &gpu_count, v_info.gpus.data());
    if(res) {
        error = Throw::ExitError("GPU not Found do you have one installed", -1);
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



