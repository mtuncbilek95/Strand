#include "Renderer.h"

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

namespace Flax
{
	void Renderer::Initialize(const RendererProps& desc)
	{
		InstanceProps vkInstProp =
		{
			.appName = "Flax",
			.engineName = "Flax",
			.appVersion = Math::Vec3u(1, 0, 0),
			.engineVersion = Math::Vec3u(1, 0, 0)
		};
		m_vkInstance = NewRef<VInstance>(vkInstProp);
		m_vkDevice = NewRef<VDevice>(DeviceProps(), m_vkInstance.get());

		m_vkGraphicsQueue = m_vkDevice->CreateQueue(VK_QUEUE_GRAPHICS_BIT);
		m_vkTransferQueue = m_vkDevice->CreateQueue(VK_QUEUE_TRANSFER_BIT);

		SwapchainProps vkSwapProp =
		{
			.imageSize = { 1280, 720 },
			.imageCount = 3,
			.format = VK_FORMAT_R8G8B8A8_UNORM,
			.presentMode = VK_PRESENT_MODE_FIFO_KHR,
			.graphicsQueue = m_vkGraphicsQueue.get(),
			.windowHandler = desc.windowHandle
		};
		m_vkSwapchain = NewRef<VSwapchain>(vkSwapProp, m_vkDevice.get());

		CmdPoolProps vkGPoolProp =
		{
			.queue = m_vkGraphicsQueue.get()
		};
		m_executionCmdPool = NewRef<VCmdPool>(vkGPoolProp, m_vkDevice.get());

		for (usize i = 0; i < m_vkSwapchain->GetImageCount(); i++)
		{
			m_executionCmdBuffers.push_back(m_executionCmdPool->CreateCmdBuffer());
			m_inFlightFences.push_back(NewRef<VFence>(false, m_vkDevice.get()));
			m_imageSemaphores.push_back(NewRef<VSemaphore>(m_vkDevice.get()));
			m_presentSemaphores.push_back(NewRef<VSemaphore>(m_vkDevice.get()));
		}
		m_transferFence = NewRef<VFence>(false, m_vkDevice.get());

		ImageProps dptProp =
		{
			.imgSize = { 1280, 720, 1 },
			.imgFormat = VK_FORMAT_D32_SFLOAT,
			.imgUsage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
			.memUsage = VMA_MEMORY_USAGE_AUTO_PREFER_DEVICE,
			.memFlags = VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT
		};
		m_depthImage = NewRef<VImage>(dptProp, &*m_vkDevice);

		ViewProps dptViewProp =
		{
			.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT,
			.baseMipLevel = 0,
			.baseArrayLayer = 0
		};
		m_depthView = m_depthImage->CreateView(dptViewProp);

		RenderPassProps rpProp =
		{
			.attachments =
			{
				// Color format
				{ VK_FORMAT_R8G8B8A8_UNORM, AttachmentType::Color, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
				VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, VK_ATTACHMENT_LOAD_OP_CLEAR, VK_ATTACHMENT_STORE_OP_STORE },
				{ VK_FORMAT_D32_SFLOAT, AttachmentType::Depth, VK_IMAGE_LAYOUT_UNDEFINED,
				VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL, VK_ATTACHMENT_LOAD_OP_CLEAR, VK_ATTACHMENT_STORE_OP_STORE }
			},
			.subpasses =
			{
				{ { 0 }, 1, {}, VK_PIPELINE_BIND_POINT_GRAPHICS }
			}
		};
		m_presentPass = NewRef<VRenderPass>(rpProp, &*m_vkDevice);

		FramebufferProps fbProp =
		{
			.passRef = &*m_presentPass,
			.imageViewsPerFB = { { m_vkSwapchain->GetImageView(0), &*m_depthView }, { m_vkSwapchain->GetImageView(1), &*m_depthView }, { m_vkSwapchain->GetImageView(2), &*m_depthView }},
			.fbSize = { 1280, 720, 1 }
		};
		m_presentFBO = NewRef<VFramebuffer>(fbProp, &*m_vkDevice);
	}

	void Renderer::Run()
	{
		// Do compute in one thread
		// Do transfer in another thread
		
		// Acquire Next Image first then handle secondary buffers
		u32 index = m_vkSwapchain->AcquireNextImage(m_imageSemaphores[m_currentIndex].get(), nullptr);

		// Do the secondary work for renderSystem

		m_executionCmdBuffers[index]->BeginRecord(InheritanceProps());
		RenderPassBeginParams beginParams =
		{
			.renderPass = &*m_presentPass,
			.framebuffer = &*m_presentFBO,
			.frameIndex = index,
			.renderArea = { 1280, 720 },
			.clearValues = { { 1.0f, 0.0f, 1.0f, 1.0f }, { 1.0f, 0 } },
			.contents = VK_SUBPASS_CONTENTS_SECONDARY_COMMAND_BUFFERS
		};
		m_executionCmdBuffers[index]->BeginRenderPass(beginParams);
		m_executionCmdBuffers[index]->ExecuteCommands({});
		m_executionCmdBuffers[index]->EndRenderPass();
		m_executionCmdBuffers[index]->EndRecord();

		m_vkGraphicsQueue->Submit({ &*m_executionCmdBuffers[index] }, { &*m_imageSemaphores[m_currentIndex] }, { &*m_presentSemaphores[index] }, &*m_inFlightFences[index], VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT);
		m_vkSwapchain->Present({ &*m_presentSemaphores[index] });

		m_currentIndex = (index + 1) % m_vkSwapchain->GetImageCount();

		m_inFlightFences[index]->Wait();
		m_inFlightFences[index]->Reset();
	}

	void Renderer::Stop()
	{
		m_vkDevice->WaitDeviceIdle();
	}

	namespace
	{
		struct RendererRegistry
		{
			RendererRegistry()
			{
				ServiceLocator::Register<Renderer>(NewRef<Renderer>());
			}
		};

		static RendererRegistry rendererRegistry;
	}
}
