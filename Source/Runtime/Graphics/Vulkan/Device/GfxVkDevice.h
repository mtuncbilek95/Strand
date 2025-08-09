/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Device/GfxDevice.h>

#include <vulkan/vulkan.h>
#include <vma/vk_mem_alloc.h>
#include <Volk/volk.h>

namespace Strand
{
	class GfxVkDevice final : public GfxDevice
	{
		struct QueueFamily
		{
			QueueFamily() : m_familyIndex(255), m_queueCount(0), m_requestedCount(0) {}
			~QueueFamily() {}

			VkQueue GetFreeQueue();
			void FillQueues(VkDevice device);

			u32 m_familyIndex;
			u32 m_queueCount;
			u32 m_requestedCount;
			Vector<VkQueue> m_queues;
		};

	public:
		GfxVkDevice(const GfxDeviceDesc& desc, GfxInstance* pInstance);
		~GfxVkDevice() override final;

		void* Device() const override final;
		void* Instance() const override final;
		void* Adapter() const override final;
		void* Allocator() const override final;

		void WaitIdle() const override final;

		Ref<GfxQueue> CreateQueue(QueueType type) override final;
		Ref<GfxImage> CreateImage(const GfxImageDesc& desc) override final;
		Ref<GfxImageView> CreateView(const GfxImageViewDesc& desc) override final;
		Ref<GfxSwapchain> CreateSwapchain(const GfxSwapchainDesc& desc) override final;
		Ref<GfxBuffer> CreateBuffer(const GfxBufferDesc& desc) override final;
		Ref<GfxPipeline> CreateGraphicsPipeline(const GfxGraphicsPipelineDesc& desc) override final;
		Ref<GfxFence> CreateSyncFence(const GfxFenceDesc& desc) override final;
		Ref<GfxSemaphore> CreateSyncSemaphore(const GfxSemaphoreDesc& desc) override final;
		Ref<GfxDescriptorLayout> CreateDescriptorLayout(const GfxDescriptorLayoutDesc& desc) override final;
		Ref<GfxDescriptorPool> CreateDescriptorPool(const GfxDescriptorPoolDesc& desc) override final;
		Ref<GfxDescriptorSet> CreateDescriptorSet(const GfxDescriptorSetDesc& desc) override final;
		Ref<GfxSampler> CreateSampler(const GfxSamplerDesc& desc) override final;
		Ref<GfxShader> CreateShader(const GfxShaderDesc& desc) override final;
		Ref<GfxCommandPool> CreateCommandPool(const GfxCommandPoolDesc& desc) override final;
		Ref<GfxCommandBuffer> CreateCommandBuffer(const GfxCommandBufferDesc& desc) override final;
		Ref<GfxFramebuffer> CreateFramebuffer(const GfxFramebufferDesc& desc) override final;
		Ref<GfxRenderPass> CreateRenderPass(const GfxRenderPassDesc& desc) override final;

	private:
		VkDevice m_device;
		VkInstance m_instance;
		VkPhysicalDevice m_adapter;
		VmaAllocator m_allocator;

		QueueFamily m_graphicsQueue;
		QueueFamily m_computeQueue;
		QueueFamily m_transferQueue;
	};
}
