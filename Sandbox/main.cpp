#include <Runtime/Window/BasicWindow.h>
#include <Runtime/Vulkan/Instance/VInstance.h>
#include <Runtime/Vulkan/Device/VDevice.h>
#include <Runtime/Vulkan/Shader/VShader.h>

#include <Runtime/Thread/ThreadPool.h>

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

    window.Show();

    while (window.IsActive())
    {
        window.ProcessEvents();
    }

    window.Hide();

    return 0;
}