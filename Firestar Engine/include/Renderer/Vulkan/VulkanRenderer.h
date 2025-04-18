#pragma once
#include "Renderer/IRenderer.h"

#include "Renderer/Vulkan/Utils/VulkanUtils.h"
#include "FirestarEngine.h"

//Vulkan 
class VulkanRenderer : public IRenderer
{
public:
    VulkanRenderer(FirestarEngine* engine);
    Throw* Initialise(GameInfo *info) override;
    void Draw() override;
    void Clear() override;
    void Shutdown() override;
    std::string GetError() override;
    ~VulkanRenderer();
private:
    std::string v_error = ""; 
    VulkanInfo v_info;

    FirestarEngine* s_engine;
};


