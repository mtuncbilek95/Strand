/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Vulkan/Object/VObject.h>

namespace Flax
{
	class VQueue;
	class VSemaphore;
	class VFence;
	class VImage;
	class VImageView;

	struct SwapchainProps final
	{
		Math::Vec2u imageSize = { 1600, 900 };
		u8 imageCount = 3;
		VkFormat format = VK_FORMAT_R8G8B8A8_UNORM;
		VkPresentModeKHR presentMode = VK_PRESENT_MODE_FIFO_KHR;
		VQueue* graphicsQueue = nullptr;
#if defined(FLAX_WINDOWS)
        void* windowHandler = nullptr;
#endif
	};

	class VSwapchain final : public VObject
	{
	public:
		VSwapchain(const SwapchainProps& desc, VDevice* pDevice);
		~VSwapchain() override final;

		VkSwapchainKHR GetVkSwapchain() const { return m_swapchain; }
		VkSurfaceKHR GetVkSurface() const { return m_surface; }
		VkFormat GetVkFormat() const { return m_props.format; }
		VkPresentModeKHR GetVkPresentMode() const { return m_props.presentMode; }
		Math::Vec2u GetImageSize() const { return m_props.imageSize; }
		u8 GetImageCount() const { return m_props.imageCount; }

		VImage* GetCurrentImage() const { return &*m_images[m_requestedIndex]; }
		VImageView* GetCurrentView() const { return &*m_views[m_requestedIndex]; }
		VImageView* GetImageView(u32 index) const { return &*m_views[index]; }

		u32 AcquireNextImage(VSemaphore* semaphore, VFence* fence);
		void Present(const Vector<VSemaphore*>& semaphore) const;
		void Resize(const Math::Vec2u& newSize);

	private:
		SwapchainProps m_props;

		VkSwapchainKHR m_swapchain;
		VkSurfaceKHR m_surface;

		Vector<Ref<VImage>> m_images;
		Vector<Ref<VImageView>> m_views;

		VkFence m_barrierFence;
		VkCommandPool m_barrierPool;
		VkCommandBuffer m_barrierBuffer;

		u32 m_requestedIndex = 0;
	};
}