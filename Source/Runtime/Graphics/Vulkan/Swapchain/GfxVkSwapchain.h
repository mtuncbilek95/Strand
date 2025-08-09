/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Swapchain/GfxSwapchain.h>

#include <vulkan/vulkan.h>

namespace Strand
{
	class GfxVkSwapchain final : public GfxSwapchain
	{
	public:
		GfxVkSwapchain(const GfxSwapchainDesc& desc, GfxDevice* pDevice);
		~GfxVkSwapchain() override final;

		u32 AcquireNextImage(GfxSemaphore* signal, GfxFence* fence) override final;
		void Present(const Vector<GfxSemaphore*>& waits) const override final;
		void Resize(const Math::Vec2u& newSize) override final;
		
	private:
		VkSwapchainKHR m_swapchain;
		VkSurfaceKHR m_surface;

		VkFence m_barrierFence;
		VkCommandPool m_barrierPool;
		VkCommandBuffer m_barrierBuffer;

		u32 m_requestedIndex;
	};
}