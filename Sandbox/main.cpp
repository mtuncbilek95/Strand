#include <Runtime/Window/BasicWindow.h>
#include <Runtime/Vulkan/Instance/VInstance.h>
#include <Runtime/Vulkan/Device/VDevice.h>
#include <Runtime/Vulkan/Shader/VShader.h>

#include <Runtime/EntityComponent/Scene.h>
#include <Runtime/EntityComponent/Entity.h>
#include <Runtime/EntityComponent/Component/TransformComponent.h>

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

    Scene scene;
    Ref<Entity> entt1 = scene.AddEntity();
    Ref<Entity> entt2 = scene.AddEntity();
    Ref<Entity> entt3 = scene.AddEntity();

    entt1->AddComponent<TransformComponent>();
    entt1->AddComponent<TransformComponent>();

    window.Show();
    while (window.IsActive())
    {
        window.ProcessEvents();
    }
    window.Hide();

    return 0;
}