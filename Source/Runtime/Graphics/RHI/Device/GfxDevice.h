/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>

#include <Runtime/Graphics/RHI/Device/GfxDeviceDesc.h>
#include <Runtime/Graphics/RHI/Queue/GfxQueueDesc.h>
#include <Runtime/Graphics/RHI/Image/GfxImageDesc.h>
#include <Runtime/Graphics/RHI/Image/GfxImageViewDesc.h>
#include <Runtime/Graphics/RHI/Swapchain/GfxSwapchainDesc.h>
#include <Runtime/Graphics/RHI/Buffer/GfxBufferDesc.h>
#include <Runtime/Graphics/RHI/Pipeline/GfxPipelineDesc.h>
#include <Runtime/Graphics/RHI/Sync/GfxFenceDesc.h>
#include <Runtime/Graphics/RHI/Sync/GfxSemaphoreDesc.h>
#include <Runtime/Graphics/RHI/Descriptor/GfxDescriptorLayoutDesc.h>
#include <Runtime/Graphics/RHI/Descriptor/GfxDescriptorPoolDesc.h>
#include <Runtime/Graphics/RHI/Descriptor/GfxDescriptorSetDesc.h>
#include <Runtime/Graphics/RHI/Sampler/GfxSamplerDesc.h>
#include <Runtime/Graphics/RHI/Shader/GfxShaderDesc.h>
#include <Runtime/Graphics/RHI/Command/GfxCommandPoolDesc.h>
#include <Runtime/Graphics/RHI/Command/GfxCommandBufferDesc.h>
#include <Runtime/Graphics/RHI/Framebuffer/GfxFramebufferDesc.h>
#include <Runtime/Graphics/RHI/RenderPass/GfxRenderPassDesc.h>

namespace Flax
{
	class GfxInstance;
	class GfxQueue;
	class GfxSwapchain;
	class GfxImage;
	class GfxImageView;
	class GfxBuffer;
	class GfxPipeline;
	class GfxFence;
	class GfxSemaphore;
	class GfxDescriptorLayout;
	class GfxDescriptorPool;
	class GfxDescriptorSet;
	class GfxSampler;
	class GfxShader;
	class GfxCommandPool;
	class GfxCommandBuffer;
	class GfxFramebuffer;
	class GfxRenderPass;

	class GfxDevice
	{
	public:
		GfxDevice(const GfxDeviceDesc& desc, GfxInstance* pInstance);
		virtual ~GfxDevice() = default;

		virtual void* Device() const = 0;
		virtual void* Instance() const = 0;
		virtual void* Adapter() const = 0;
		virtual void* Allocator() const = 0;

		virtual void WaitIdle() const = 0;

		virtual Ref<GfxQueue> CreateQueue(QueueType type) = 0;
		virtual Ref<GfxImage> CreateImage(const GfxImageDesc& desc) = 0;
		virtual Ref<GfxSwapchain> CreateSwapchain(const GfxSwapchainDesc& desc) = 0;
		virtual Ref<GfxImageView> CreateView(const GfxImageViewDesc& desc) = 0;
		virtual Ref<GfxBuffer> CreateBuffer(const GfxBufferDesc& desc) = 0;
		virtual Ref<GfxPipeline> CreateGraphicsPipeline(const GfxGraphicsPipelineDesc& desc) = 0;
		virtual Ref<GfxFence> CreateSyncFence(const GfxFenceDesc& desc) = 0;
		virtual Ref<GfxSemaphore> CreateSyncSemaphore(const GfxSemaphoreDesc& desc) = 0;
		virtual Ref<GfxDescriptorLayout> CreateDescriptorLayout(const GfxDescriptorLayoutDesc& desc) = 0;
		virtual Ref<GfxDescriptorPool> CreateDescriptorPool(const GfxDescriptorPoolDesc& desc) = 0;
		virtual Ref<GfxDescriptorSet> CreateDescriptorSet(const GfxDescriptorSetDesc& desc) = 0;
		virtual Ref<GfxSampler> CreateSampler(const GfxSamplerDesc& desc) = 0;
		virtual Ref<GfxShader> CreateShader(const GfxShaderDesc& desc) = 0;
		virtual Ref<GfxCommandPool> CreateCommandPool(const GfxCommandPoolDesc& desc) = 0;
		virtual Ref<GfxCommandBuffer> CreateCommandBuffer(const GfxCommandBufferDesc& desc) = 0;
		virtual Ref<GfxFramebuffer> CreateFramebuffer(const GfxFramebufferDesc& desc) = 0;
		virtual Ref<GfxRenderPass> CreateRenderPass(const GfxRenderPassDesc& desc) = 0;

	private:
		GfxDeviceDesc m_desc;
	};
}