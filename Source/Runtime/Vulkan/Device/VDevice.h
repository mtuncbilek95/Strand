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
	class VInstance;
	class VQueue;
	class VSemaphore;
	class VFence;

	struct DeviceProps final
	{
		u32 graphicsQueueCount = 1;
		u32 computeQueueCount = 1;
		u32 transferQueueCount = 1;
	};

	class VDevice final
	{
		struct QueueFamily
		{
			QueueFamily() : m_familyIndex(255), m_queueCount(0), m_requestedCount(0) {};
			~QueueFamily() = default;

			VkQueue GetFreeQueue()
			{
				if (m_queueCount > 0)
				{
					VkQueue queue = m_queues.back();
					m_queues.pop_back();
					m_queueCount--;
					return queue;
				}

				return VK_NULL_HANDLE;
			}

			void FillQueues(VkDevice device)
			{
				for (u32 i = 0; i < m_requestedCount; i++)
				{
					VkQueue queue;
					vkGetDeviceQueue(device, m_familyIndex, i, &queue);
					m_queues.push_back(queue);
				}
			}

			u32 m_familyIndex;
			u32 m_queueCount;
			u32 m_requestedCount;
			Vector<VkQueue> m_queues;
		};

	public:
		VDevice(const DeviceProps& desc, VInstance* pInstance);
		~VDevice();

		inline VkDevice GetVkDevice() const { return m_device; }
		inline VkPhysicalDevice GetVkAdapter() const { return m_adapter; }
		inline VkInstance GetVkInstance() const { return m_instance; }
        inline VmaAllocator GetVkAllocator() const { return m_allocator; }

		Ref<VQueue> CreateQueue(VkQueueFlags queueType);

		u32 FindMemoryType(VkMemoryPropertyFlags properties) const;

		void WaitForIdle() const;
		void WaitForFence(const Vector<VFence*>& fences) const;
		void ResetFence(const Vector<VFence*>& fences) const;

	private:
		DeviceProps m_props;

		VkInstance m_instance;
		VkDevice m_device;
		VkPhysicalDevice m_adapter;
        VmaAllocator m_allocator;

		QueueFamily m_graphicsQueueFamily;
		QueueFamily m_computeQueueFamily;
		QueueFamily m_transferQueueFamily;
	};
}