/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <vulkan/vulkan.h>

#include <vma/vk_mem_alloc.h>

namespace Flax
{
	class FvkImage;
	class FvkImageView;

	struct FvkDebug
	{
		static void Assert(VkResult result, const String& target);
	};

	class FvkContext : public Singleton<FvkContext>
	{
	public:
		FvkContext();
		~FvkContext();

		void CreateContext();

		inline VkInstance Instance() const { return m_instance; }
		inline VkPhysicalDevice Adapter() const { return m_adapter; }
		inline VkDevice Device() const { return m_device; }
		inline VmaAllocator Allocator() const { return m_allocator; }

		inline VkQueue GraphicsQueue() const { return m_graphicsQueue; }
		inline VkQueue TransferQueue() const { return m_transferQueue; }

	private:
		void createInstance();
		void pickAdapter();
		void createDevice();
		void pickQueues();
		void createSurface();
		void createSwapchain();

	private:
		VkInstance m_instance;
		VkPhysicalDevice m_adapter;
		VkDevice m_device;
		VkSwapchainKHR m_swapchain;
		VkSurfaceKHR m_surface;

		Vector<Ref<FvkImage>> m_images;
		Vector<Ref<FvkImageView>> m_views;

		VkFence m_barrierFence;
		VkCommandPool m_barrierPool;
		VkCommandBuffer m_barrierBuffer;

		u32 m_requestedIndex = 0;

		VkQueue m_graphicsQueue;
		u32 m_graphicsIndex;
		VkQueue m_transferQueue;
		u32 m_transferIndex;

#if defined(FLAX_DEBUG)
		VkDebugUtilsMessengerEXT m_debugMessenger;
#endif

		VmaAllocator m_allocator;
	};
}
