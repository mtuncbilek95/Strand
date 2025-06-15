/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Swapchain/GfxSwapchain.h>

#include <vulkan/vulkan.h>

namespace Flax
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