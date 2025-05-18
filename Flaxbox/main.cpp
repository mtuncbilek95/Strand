#include <Runtime/Window/BasicWindow.h>
#include <Runtime/Vulkan/Instance/VInstance.h>
#include <Runtime/Vulkan/Device/VDevice.h>
#include <Runtime/Vulkan/Queue/VQueue.h>
#include <Runtime/Vulkan/Swapchain/VSwapchain.h>
#include <Runtime/Vulkan/Command/VCmdPool.h>
#include <Runtime/Vulkan/Command/VCmdBuffer.h>
#include <Runtime/Vulkan/Sync/VFence.h>
#include <Runtime/Vulkan/Sync/VSemaphore.h>
#include <Runtime/Vulkan/RenderPass/VRenderPass.h>
#include <Runtime/Vulkan/Framebuffer/VFramebuffer.h>
#include <Runtime/Vulkan/Descriptor/VDescriptorLayout.h>
#include <Runtime/Vulkan/Descriptor/VDescriptorPool.h>
#include <Runtime/Vulkan/Descriptor/VDescriptorSet.h>
#include <Runtime/Vulkan/Shader/VShader.h>
#include <Runtime/Vulkan/Pipeline/VPipeline.h>
#include <Runtime/Vulkan/Image/VImage.h>
#include <Runtime/Vulkan/Image/VImageView.h>

#include "MeshObject.h"

using namespace Flax;

int main()
{
	WindowProps w11Props =
	{
		.windowName = "Flax",
		.windowSize = { 1280, 720 },
		.windowMode = WindowMode::Windowed
	};
	Ref<BasicWindow> window = NewRef<BasicWindow>(w11Props);

	InstanceProps vkInstProp =
	{
		.appName = "Flax",
		.engineName = "Flax",
		.appVersion = Math::Vec3u(1, 0, 0),
		.engineVersion = Math::Vec3u(1, 0, 0)
	};
	Ref<VInstance> vkInstance = NewRef<VInstance>(vkInstProp);
	Ref<VDevice> vkDevice = NewRef<VDevice>(DeviceProps(), vkInstance.get());

	Ref<VQueue> vkGQueue = vkDevice->CreateQueue(VK_QUEUE_GRAPHICS_BIT);
	Ref<VQueue> vkTQueue = vkDevice->CreateQueue(VK_QUEUE_TRANSFER_BIT);

	SwapchainProps vkSwapProp =
	{
		.imageSize = { 1280, 720 },
		.imageCount = 3,
		.format = VK_FORMAT_R8G8B8A8_UNORM,
		.presentMode = VK_PRESENT_MODE_FIFO_KHR,
		.graphicsQueue = vkGQueue.get(),
		.windowHandler = window->GetHandle()
	};
	Ref<VSwapchain> vkSwapchain = NewRef<VSwapchain>(vkSwapProp, vkDevice.get());

	CmdPoolProps vkGPoolProp =
	{
		.queue = vkGQueue.get()
	};
	Ref<VCmdPool> vkGPool = NewRef<VCmdPool>(vkGPoolProp, vkDevice.get());
	Vector<Ref<VCmdBuffer>> vkGBuffers;

	for (usize i = 0; i < vkSwapchain->GetImageCount(); i++)
		vkGBuffers.push_back(vkGPool->CreateCmdBuffer());

	Ref<VFence> vkFence = NewRef<VFence>(false, vkDevice.get());

	Vector<Ref<VSemaphore>> vkSemaphores;
	for (usize i = 0; i < vkSwapchain->GetImageCount(); i++)
		vkSemaphores.push_back(NewRef<VSemaphore>(vkDevice.get()));

	ImageProps dptProp =
	{
		.imgSize = { 1280, 720, 1 },
		.imgFormat = VK_FORMAT_D32_SFLOAT,
		.imgUsage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
		.memUsage = VMA_MEMORY_USAGE_AUTO_PREFER_DEVICE,
		.memFlags = VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT
	};
	Ref<VImage> vkDepth = NewRef<VImage>(dptProp, &*vkDevice);

	ViewProps dptViewProp =
	{
		.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT,
		.baseMipLevel = 0,
		.baseArrayLayer = 0
	};
	Ref<VImageView> vkDepthView = vkDepth->CreateView(dptViewProp);

	RenderPassProps rpProp =
	{
		.attachments =
		{
			// Color format
			{ VK_FORMAT_R8G8B8A8_UNORM, AttachmentType::Color, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
			VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, VK_ATTACHMENT_LOAD_OP_CLEAR, VK_ATTACHMENT_STORE_OP_STORE },
			{ VK_FORMAT_D32_SFLOAT, AttachmentType::Depth, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
			VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL, VK_ATTACHMENT_LOAD_OP_CLEAR, VK_ATTACHMENT_STORE_OP_STORE }
		},
		.subpasses =
		{
			{ { 0 }, 1, {}, VK_PIPELINE_BIND_POINT_GRAPHICS }
		}
	};
	Ref<VRenderPass> vkRenderPass = NewRef<VRenderPass>(rpProp, &*vkDevice);

	FramebufferProps fbProp =
	{
		.passRef = &*vkRenderPass,
		.imageViewsPerFB = { { vkSwapchain->GetImageView(0), &*vkDepthView }, {vkSwapchain->GetImageView(1), &*vkDepthView }, {vkSwapchain->GetImageView(2), &*vkDepthView }},
		.fbSize = { 1280, 720, 1 }
	};
	Ref<VFramebuffer> vkFramebuffer = NewRef<VFramebuffer>(fbProp, &*vkDevice);

	DescLayoutProps vkMeshDescLayoutProps =
	{
		.bindings =
		{
			{ 0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1, VK_SHADER_STAGE_VERTEX_BIT },
			{ 1, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1, VK_SHADER_STAGE_VERTEX_BIT }
		},
		.createFlags = 0
	};
	Ref<VDescLayout> vkMeshDescLayout = NewRef<VDescLayout>(vkMeshDescLayoutProps, &*vkDevice);

	DescPoolProps vkDescPoolProps =
	{
		.poolSizes =
		{
			{ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 2 }
		},
		.maxSets = 2
	};
	Ref<VDescPool> vkDescPool = NewRef<VDescPool>(vkDescPoolProps, &*vkDevice);
	Ref<VDescSet> vkDescSet = NewRef<VDescSet>(DescSetProps({ vkMeshDescLayout.get(), vkDescPool.get() }), &*vkDevice);

	ShaderProps vertProp =
	{
		.shaderPath = R"(D:\Projects\Flax\Flaxbox\TestObj.vert)",
		.includePath = "",
		.entryPoint = "main",
		.shaderStage = VK_SHADER_STAGE_VERTEX_BIT
	};
	Ref<VShader> vkVShader = NewRef<VShader>(vertProp, &*vkDevice);

	ShaderProps fragProp =
	{
		.shaderPath = R"(D:\Projects\Flax\Flaxbox\TestObj.frag)",
		.includePath = "",
		.entryPoint = "main",
		.shaderStage = VK_SHADER_STAGE_FRAGMENT_BIT
	};
	Ref<VShader> vkFShader = NewRef<VShader>(fragProp, &*vkDevice);

	GraphicsPipelineProps vkMeshGrapProp =
	{
		.layouts = {&*vkMeshDescLayout},
		.shaderStages = {&*vkVShader, &*vkFShader},
		.inputAssembler = {VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, false, {{VK_VERTEX_INPUT_RATE_VERTEX, {VK_FORMAT_R32G32B32_SFLOAT, VK_FORMAT_R32G32B32_SFLOAT,
		VK_FORMAT_R32G32B32_SFLOAT, VK_FORMAT_R32G32B32_SFLOAT, VK_FORMAT_R32G32B32A32_SFLOAT, VK_FORMAT_R32G32_SFLOAT }}}},
		.viewportState = {false, {0.f, 0.f, (f32)vkSwapchain->GetImageSize()[0], (f32)vkSwapchain->GetImageSize()[1], 0.f, 1.f},
		false, {{0, 0}, {vkSwapchain->GetImageSize()[0], vkSwapchain->GetImageSize()[1]}}},
		.rasterizerState = {true, 0.f, 1.f, 0.f, VK_POLYGON_MODE_FILL, VK_CULL_MODE_BACK_BIT, VK_FRONT_FACE_CLOCKWISE},
		.blendState = {true, VK_LOGIC_OP_COPY, {{false, VK_BLEND_FACTOR_ZERO, VK_BLEND_FACTOR_ONE, VK_BLEND_OP_ADD,
		VK_BLEND_FACTOR_ZERO, VK_BLEND_FACTOR_ONE, VK_BLEND_OP_ADD, VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT}}},
		.depthStencilState = {true, true, VK_COMPARE_OP_LESS, false, false, {}, {}, 0.f, 1.f},
		.renderPass = &*vkRenderPass
	};
	Ref<VPipeline> vkMeshPipeline = NewRef<VPipeline>(vkMeshGrapProp, &*vkDevice);

	MeshObject meshObj;
	meshObj.Load(R"(D:\Projects\_ReadOnly\glTF-Sample-Models\2.0\SciFiHelmet\glTF\SciFiHelmet.gltf)", vkTQueue.get(), &*vkDevice);
	vkDescSet->UpdateData(SetUpdateProps(
		{
			{ {meshObj.GetModelBuffer()}, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1, 0, 0, 0},
			{ {meshObj.GetVPBuffer()}, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1, 0, 0, 1}
		}));

	window->Show();
	while (window->IsActive())
	{
		window->ProcessEvents();
		u32 index = vkSwapchain->AcquireNextImage(nullptr, vkFence.get());
		vkFence->Wait();
		vkFence->Reset();

		vkGBuffers[index]->BeginRecord();
		RenderPassBeginParams beginParams =
		{
			.renderPass = &*vkRenderPass,
			.framebuffer = &*vkFramebuffer,
			.frameIndex = index,
			.renderArea = { 1280, 720 },
			.clearValues = { { 1.0f, 0.0f, 1.0f, 1.0f }, { 1.0f, 0 } },
			.contents = VK_SUBPASS_CONTENTS_INLINE
		};
		vkGBuffers[index]->BeginRenderPass(beginParams);

		vkGBuffers[index]->BindPipeline(&*vkMeshPipeline);
		vkGBuffers[index]->BindDescriptors({ &*vkDescSet });
		vkGBuffers[index]->BindVertexBuffers({ meshObj.GetGpuBuffer() });
		vkGBuffers[index]->DrawCommon(meshObj.GetVertexCount(), 0, 0, 1);

		vkGBuffers[index]->EndRenderPass();
		vkGBuffers[index]->EndRecord();

		vkGQueue->Submit({ vkGBuffers[index].get() }, {}, { vkSemaphores[index].get() }, nullptr, VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT);
		vkSwapchain->Present({ vkSemaphores[index].get() });
	}

	vkDevice->WaitDeviceIdle();
	window->Hide();
}