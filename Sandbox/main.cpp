#include <Runtime/Window/BasicWindow.h>

#include <Runtime/Vulkan/Instance/VInstance.h>
#include <Runtime/Vulkan/Device/VDevice.h>
#include <Runtime/Vulkan/Shader/VShader.h>
#include <Runtime/Vulkan/Swapchain/VSwapchain.h>

#include <Runtime/Thread/ThreadPool.h>

#include <Runtime/Resource/Importer/MeshImporter.h>

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

    auto vkQueue = vkDevice.CreateQueue(VK_QUEUE_GRAPHICS_BIT);
    
    SwapchainProps swcProp =
    {
        .graphicsQueue = &*vkQueue,
        .windowHandler = window.GetNativeWindow()
    };
    VSwapchain vkSwapchain(swcProp, &vkDevice);

    window.Show();

    while (window.IsActive())
    {
        window.ProcessEvents();
    }

    window.Hide();

    return 0;
}