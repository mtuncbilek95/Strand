#include <Runtime/Window/BasicWindow.h>
#include <Runtime/Vulkan/Instance/VInstance.h>
#include <Runtime/Vulkan/Device/VDevice.h>
#include <Runtime/Vulkan/Shader/VShader.h>

using namespace Flax;

int main()
{
    BasicWindow window;
    
    InstanceProps instanceProps =
    {
        .appName = "Flax",
        .engineName = "Flax Engine",
        .appVersion = { 1, 0, 0 },
        .engineVersion = { 1, 0, 0 }
    };
    VInstance vkInstance(instanceProps);
    VDevice vkDevice(DeviceProps(), &vkInstance);

    ShaderProps shaderProps =
    {
        .shaderPath = "TestShader.vert",
        .shaderStage = VK_SHADER_STAGE_VERTEX_BIT,
    };
    VShader shader(shaderProps, &vkDevice);

    window.Show();
    while (window.IsActive())
    {
        window.ProcessEvents();
    }
    window.Hide();

    return 0;
}