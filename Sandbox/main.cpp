#include <Runtime/Window/BasicWindow.h>

#include <Runtime/Vulkan/Instance/VInstance.h>
#include <Runtime/Vulkan/Device/VDevice.h>
#include <Runtime/Vulkan/Shader/VShader.h>
#include <Runtime/Vulkan/Buffer/VBuffer.h>
#include <Runtime/Vulkan/Pipeline/VPipeline.h>
#include <Runtime/Vulkan/Swapchain/VSwapchain.h>
#include <Runtime/Vulkan/Image/VImage.h>
#include <Runtime/Vulkan/Image/VImageView.h>
#include <Runtime/Vulkan/Queue/VQueue.h>
#include <Runtime/Vulkan/Sync/VSemaphore.h>
#include <Runtime/Vulkan/Sync/VFence.h>
#include <Runtime/Vulkan/Command/VCmdPool.h>
#include <Runtime/Vulkan/Command/VCmdBuffer.h>
#include <Runtime/Vulkan/RenderPass/VRenderPass.h>
#include <Runtime/Vulkan/Framebuffer/VFramebuffer.h>

#include <Runtime/Resource/Importer/MeshImporter.h>
#include "MeshObject.h"

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

    // ========== Necessary Synchronization ========== //
    auto vkFence = MakeShared<VFence>(false, &vkDevice);
    Vector<Ref<VSemaphore>> vkRenderSemaphores = { MakeShared<VSemaphore>(&vkDevice), MakeShared<VSemaphore>(&vkDevice) };

    // ========== Necessary Queues ========== //
    auto vkGraphQueue = vkDevice.CreateQueue(VK_QUEUE_GRAPHICS_BIT);
    auto vkTransQueue = vkDevice.CreateQueue(VK_QUEUE_TRANSFER_BIT);

    // ========== Swapchain ========== //
    SwapchainProps swcProp =
    {
        .graphicsQueue = &*vkGraphQueue,
        .windowHandler = window.GetNativeWindow()
    };
    VSwapchain vkSwapchain(swcProp, &vkDevice);

    // ========== Depth Buffer ========== //
    ImageProps dptProp =
    {
        .imageSize = { 1600, 900, 1 },
        .imageFormat = VK_FORMAT_D32_SFLOAT,
        .imageUsage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
        .memoryUsage = VMA_MEMORY_USAGE_GPU_ONLY
    };
    VImage vkDepth = VImage(dptProp, &vkDevice);

    ViewProps dptViewProp =
    {
        .aspectFlag = VK_IMAGE_ASPECT_DEPTH_BIT,
        .baseMipLevel = 0,
        .baseArrayLayer = 0
    };
    auto vkDepthView = vkDepth.CreateView(dptViewProp);

    // ========== Singular Command Buffer ========== //
    CmdPoolProps poolProp =
    {
        .queue = &*vkGraphQueue,
        .flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT
    };
    VCmdPool loopPool(poolProp, &vkDevice);

    CmdBufferProps tsfCmdProp =
    {
        .cmdLevel = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
        .pool = &loopPool
    };
    auto loopBuffer = loopPool.CreateCmdBuffer();

    // ========== RenderPass ========== //
    RenderPassProps rpProp =
    {
        .attachments =
        {
            // Color format
            { VK_FORMAT_R8G8B8A8_UNORM, AttachmentType::Color, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
            VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, VK_ATTACHMENT_LOAD_OP_CLEAR, VK_ATTACHMENT_STORE_OP_STORE },
            // Depth format
            { VK_FORMAT_D32_SFLOAT, AttachmentType::Depth, VK_IMAGE_LAYOUT_UNDEFINED,
            VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL, VK_ATTACHMENT_LOAD_OP_CLEAR, VK_ATTACHMENT_STORE_OP_STORE }
        },
        .subpasses =
        {
            { { 0 }, 1, {}, VK_PIPELINE_BIND_POINT_GRAPHICS }
        }
    };
    VRenderPass vkRenderPass = VRenderPass(rpProp, &vkDevice);

    // ========== Framebuffer ========== //
    FramebufferProps fbProp =
    {
        .passRef = &vkRenderPass,
        .imageViewsPerFB = { { vkSwapchain.GetImageView(0), &*vkDepthView }, {vkSwapchain.GetImageView(1), &*vkDepthView }},
        .fbSize = { 1600, 900, 1 }
    };
    VFramebuffer vkFramebuffer(fbProp, &vkDevice);

    // ========== Shader ========== //
    ShaderProps vertProp =
    {
        .shaderPath = R"(D:\Projects\Flax\Sandbox\TestObj.vert)",
        .includePath = "",
        .entryPoint = "main",
        .shaderStage = VK_SHADER_STAGE_VERTEX_BIT
    };
    auto vkVShader = MakeShared<VShader>(vertProp, &vkDevice);

    ShaderProps fragProp =
    {
        .shaderPath = R"(D:\Projects\Flax\Sandbox\TestObj.frag)",
        .includePath = "",
        .entryPoint = "main",
        .shaderStage = VK_SHADER_STAGE_FRAGMENT_BIT
    };
    auto vkFShader = MakeShared<VShader>(fragProp, &vkDevice);

    window.Show();

    int test = 0;
    bool yolo = false;

    MeshObject meshObj;
    
    while (window.IsActive())
    {
        window.ProcessEvents();

        if (test++ > 250 && !yolo)
        {
            meshObj.Load(R"(D:\Projects\glTF-Sample-Models\2.0\SciFiHelmet\glTF\SciFiHelmet.gltf)", vkTransQueue.get(), &vkDevice);
            test = 0;
            yolo = true;
        }

        u32 index = vkSwapchain.AcquireNextImage(nullptr, &*vkFence);
        vkFence->Wait();
        vkFence->Reset();

        loopBuffer->BeginRecord();
        RenderPassBeginParams beginParams =
        {
            .renderPass = &vkRenderPass,
            .framebuffer = &vkFramebuffer,
            .frameIndex = index,
            .renderArea = { { 0, 0 }, { 1600, 900 } },
            .clearValues = { { 1.0f, 0.0f, 0.0f, 1.0f }, { 1.0f, 0 } },
            .contents = VK_SUBPASS_CONTENTS_INLINE
        };
        loopBuffer->BeginRenderPass(beginParams);
        loopBuffer->EndRenderPass();
        loopBuffer->EndRecord();
        vkGraphQueue->Submit({ &*loopBuffer }, {}, { &*vkRenderSemaphores[index] }, nullptr, VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT);

        vkSwapchain.Present({ &*vkRenderSemaphores[index] });
    }

    vkDevice.WaitForIdle();

    window.Hide();

    return 0;
}