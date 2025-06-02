/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Device/GfxDevice.h>

#include <vulkan/vulkan.h>
#include <vma/vk_mem_alloc.h>
#include <Volk/volk.h>

namespace Flax
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

		Ref<GfxQueue> CreateQueue(QueueType type) override final;
		Ref<GfxImage> CreateImage(const GfxImageDesc& desc) override final;
		Ref<GfxImageView> CreateView(const GfxImageViewDesc& desc) override final;
		Ref<GfxSwapchain> CreateSwapchain(const GfxSwapchainDesc& desc) override final;
		Ref<GfxBuffer> CreateBuffer(const GfxBufferDesc& desc) override final { return nullptr; }
		Ref<GfxPipeline> CreateGraphicsPipeline(const GfxGraphicsPipelineDesc& desc) override final { return nullptr; }
		Ref<GfxFence> CreateSyncFence(const GfxFenceDesc& desc) override final;
		Ref<GfxSemaphore> CreateSyncSemaphore(const GfxSemaphoreDesc& desc) override final;
		Ref<GfxDescriptorLayout> CreateDescriptorLayout(const GfxDescriptorLayoutDesc& desc) override final { return nullptr; }
		Ref<GfxDescriptorPool> CreateDescriptorPool(const GfxDescriptorPoolDesc& desc) override final { return nullptr; }
		Ref<GfxDescriptorSet> CreateDescriptorSet(const GfxDescriptorSetDesc& desc) override final { return nullptr; }
		Ref<GfxSampler> CreateSampler(const GfxSamplerDesc& desc) override final;
		Ref<GfxShader> CreateShader(const GfxShaderDesc& desc) override final;
		Ref<GfxCommandPool> CreateCommandPool(const GfxCommandPoolDesc& desc) override final { return nullptr; }
		Ref<GfxCommandBuffer> CreateCommandBuffer(const GfxCommandBufferDesc& desc) override final { return nullptr; }
		Ref<GfxFramebuffer> CreateFramebuffer(const GfxFramebufferDesc& desc) override final { return nullptr; }
		Ref<GfxRenderPass> CreateRenderPass(const GfxRenderPassDesc& desc) override final { return nullptr; }

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
