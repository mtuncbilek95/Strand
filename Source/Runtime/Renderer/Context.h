/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Vulkan/Instance/VInstance.h>
#include <Runtime/Vulkan/Device/VDevice.h>
#include <Runtime/Vulkan/Queue/VQueue.h>
#include <Runtime/Vulkan/Swapchain/VSwapchain.h>
#include <Runtime/Vulkan/Command/VCmdPool.h>
#include <Runtime/Vulkan/Command/VCmdBuffer.h>
#include <Runtime/Vulkan/Sync/VFence.h>
#include <Runtime/Vulkan/Sync/VSemaphore.h>

namespace Flax
{
	class BasicWindow;

	class Context : public Singleton<Context>
	{
	public:
		Context() = default;
		~Context() = default;

		void CreateContext(BasicWindow* window);
		void DestroyContext();

		void PrepareFrame();
		void SubmitFrame();

	private:
		Ref<VInstance> m_vkInstance;
		Ref<VDevice> m_vkDevice;
		Ref<VQueue> m_vkGQueue;
		Ref<VSwapchain> m_vkSwapchain;
		Ref<VFence> m_vkFence;
		Ref<VCmdPool> m_vkGPool;
		Vector<Ref<VCmdBuffer>> m_vkGBuffers;
		Vector<Ref<VSemaphore>> m_vkSemaphores;

		u32 m_index;
	};
}