/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Data/Containers/IObject.h>

#include <vulkan/vulkan.h>
#include <vma/vk_mem_alloc.h>
#include <Volk/volk.h>

namespace Flax
{
	class VInstance;
	class VQueue;

	struct DeviceProps final
	{
		u32 gQueueCount = 1;
		u32 cQueueCount = 1;
		u32 tQueueCount = 1;
		u32 sQueueCount = 1;
	};

	class VDevice final : public IObject
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
		VDevice(const DeviceProps& desc, VInstance* pInstance);
		~VDevice() override final;

		Ref<VQueue> CreateQueue(VkQueueFlags type);

		inline VkDevice GetVkDevice() const { return m_device; }
		inline VkPhysicalDevice GetVkAdapter() const { return m_adapter; }
		inline VkInstance GetVkInstance() const { return m_instance; }
		inline VmaAllocator GetVkAllocator() const { return m_allocator; }

		void WaitDeviceIdle() const;

	private:
		DeviceProps m_props;

		VkInstance m_instance;
		VkDevice m_device;
		VkPhysicalDevice m_adapter;
		VmaAllocator m_allocator;

		QueueFamily m_graphicsQueueFamily;
		QueueFamily m_computeQueueFamily;
		QueueFamily m_transferQueueFamily;
		QueueFamily m_sparseQueueFamily;
	};
}