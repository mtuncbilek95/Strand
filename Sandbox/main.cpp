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
#include <Runtime/Vulkan/Descriptor/VDescriptorSet.h>
#include <Runtime/Vulkan/Descriptor/VDescriptorLayout.h>
#include <Runtime/Vulkan/Descriptor/VDescriptorPool.h>
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
    Vector<Ref<VSemaphore>> vkRenderSemaphores = { MakeShared<VSemaphore>(&vkDevice), MakeShared<VSemaphore>(&vkDevice), MakeShared<VSemaphore>(&vkDevice) };

    // ========== Necessary Queues ========== //
    auto vkGraphQueue = vkDevice.CreateQueue(VK_QUEUE_GRAPHICS_BIT);
    auto vkTransQueue = vkDevice.CreateQueue(VK_QUEUE_TRANSFER_BIT);

    // ========== Swapchain ========== //
    SwapchainProps swcProp =
    {
        .imageCount = 3,
        .presentMode = VK_PRESENT_MODE_FIFO_KHR,
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
        .memoryUsage = VMA_MEMORY_USAGE_GPU_ONLY,
        .createFlags = VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT
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
            { VK_FORMAT_D32_SFLOAT, AttachmentType::Depth, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
            VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL, VK_ATTACHMENT_LOAD_OP_CLEAR, VK_ATTACHMENT_STORE_OP_STORE }
        },
        .subpasses =
        {
            { { 0 }, u32_max, {}, VK_PIPELINE_BIND_POINT_GRAPHICS }
        }
    };
    VRenderPass vkRenderPass = VRenderPass(rpProp, &vkDevice);

    // ========== Framebuffer ========== //
    FramebufferProps fbProp =
    {
        .passRef = &vkRenderPass,
        .imageViewsPerFB = { { vkSwapchain.GetImageView(0), &*vkDepthView }, {vkSwapchain.GetImageView(1), &*vkDepthView }, {vkSwapchain.GetImageView(2), &*vkDepthView }},
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

    // ========== Pipeline Descriptors ========== //
    DescLayoutProps vkMeshDescLayoutProps =
    {
        .bindings =
        {
            { 0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1, VK_SHADER_STAGE_VERTEX_BIT },
            { 1, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1, VK_SHADER_STAGE_VERTEX_BIT }
        },
        .createFlags = 0
    };
    auto vkMeshDescLayout = MakeShared<VDescLayout>(vkMeshDescLayoutProps, &vkDevice);

    DescPoolProps vkDescPoolProps =
    {
        .poolSizes =
        {
            { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 2 }
        },
        .maxSets = 2
    };
    auto vkDescPool = MakeShared<VDescPool>(vkDescPoolProps, &vkDevice);
    auto vkDescSet = MakeShared<VDescSet>(DescSetProps({ vkMeshDescLayout.get(), vkDescPool.get() }), &vkDevice);

    // ========== Pipeline Layout ========== //
    GraphicsPipelineProps vkMeshGrapProp =
    {
        .layouts = {&*vkMeshDescLayout},
        .shaderStages = {&*vkVShader, &*vkFShader},
        .inputAssembler = {VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, false, {{VK_VERTEX_INPUT_RATE_VERTEX, {VK_FORMAT_R32G32B32_SFLOAT, VK_FORMAT_R32G32B32_SFLOAT,
        VK_FORMAT_R32G32B32_SFLOAT, VK_FORMAT_R32G32B32_SFLOAT, VK_FORMAT_R32G32B32A32_SFLOAT, VK_FORMAT_R32G32_SFLOAT }}}},
        .viewportState = {false, {0.f, 0.f, (f32)vkSwapchain.GetImageSize()[0], (f32)vkSwapchain.GetImageSize()[1], 0.f, 1.f},
        false, {{0, 0}, {vkSwapchain.GetImageSize()[0], vkSwapchain.GetImageSize()[1]}}},
        .rasterizerState = {true, 0.f, 1.f, 0.f, VK_POLYGON_MODE_FILL, VK_CULL_MODE_BACK_BIT, VK_FRONT_FACE_CLOCKWISE},
        .blendState = {true, VK_LOGIC_OP_COPY, {{false, VK_BLEND_FACTOR_ZERO, VK_BLEND_FACTOR_ONE, VK_BLEND_OP_ADD,
        VK_BLEND_FACTOR_ZERO, VK_BLEND_FACTOR_ONE, VK_BLEND_OP_ADD, VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT}}},
        .depthStencilState = {true, true, VK_COMPARE_OP_LESS, false, false, {}, {}, 0.f, 1.f},
        .renderPass = &vkRenderPass
    };
    auto vkMeshPipeline = MakeShared<VPipeline>(vkMeshGrapProp, &vkDevice);

    MeshObject meshObj(&vkDevice);
    meshObj.Load(R"(D:\Projects\glTF-Sample-Models\2.0\SciFiHelmet\glTF\SciFiHelmet.gltf)", vkTransQueue.get(), &vkDevice);

    // Update Descriptor Set
    vkDescSet->UpdateData(SetUpdateProps(
        {
            { {meshObj.GetModelBuffer()}, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1, 0, 0, 0},
            { {meshObj.GetVPBuffer()}, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1, 0, 0, 1}
        }));


    while (window.IsActive())
    {
        window.ProcessEvents();

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

        loopBuffer->BindPipeline(&*vkMeshPipeline);
        loopBuffer->BindDescriptors({ &*vkDescSet });
        loopBuffer->BindVertexBuffers({ meshObj.GetGpuBuffer() });
        loopBuffer->DrawCommon(meshObj.GetVertexCount(), 0, 0, 1);

        loopBuffer->EndRenderPass();
        loopBuffer->EndRecord();
        vkGraphQueue->Submit({ &*loopBuffer }, {}, { &*vkRenderSemaphores[index] }, nullptr, VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT);

        vkSwapchain.Present({ &*vkRenderSemaphores[index] });
        vkDevice.WaitForIdle();
    }

    vkDevice.WaitForIdle();

    window.Hide();

    return 0;
}