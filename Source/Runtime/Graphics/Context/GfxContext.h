/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/Context/GfxContextDesc.h>

namespace Flax
{
	class GfxInstance;
	class GfxDevice;
	class GfxQueue;
	class GfxSwapchain;
	class GfxCommandPool;
	class GfxCommandBuffer;
	class GfxSemaphore;
	class GfxFence;

	/**
	 * @class GfxContext
	 * @brief A graphics context class where it supports the whole rendering
	 * ability for the engine. It is responsible for managing the graphics 
	 * instance, device, queues, swapchain, command pools, and command buffers.
	 */
	class GfxContext : public Singleton<GfxContext>
	{
	public:
		void CreateContext(const GfxContextDesc& desc);
		void DestroyContext();

		GfxInstance* Instance() const { return m_instance.get(); }
		GfxDevice* Device() const { return m_device.get(); }
		GfxSwapchain* Swapchain() const { return m_swapchain.get(); }
		GfxQueue* GraphicsQueue() const { return m_graphicsQueue.get(); }
		GfxQueue* TransferQueue() const { return m_transferQueue.get(); }
		GfxQueue* ComputeQueue() const { return m_computeQueue.get(); }

		void BeginFrame();
		void EndFrame();
		b8 FrameCompleted() const { return m_frameCompleted; }

		void DispatchResize(const Math::Vec2u& newSize);

	private:
		Ref<GfxInstance> m_instance;
		Ref<GfxDevice> m_device;
		
		Ref<GfxQueue> m_graphicsQueue;
		Ref<GfxQueue> m_computeQueue;
		Ref<GfxQueue> m_transferQueue;

		Ref<GfxSwapchain> m_swapchain;

		Ref<GfxCommandPool> m_cmdPool;
		Vector<Ref<GfxCommandBuffer>> m_cmdBuffers;
		Vector<Ref<GfxSemaphore>> m_signalSems;
		Vector<Ref<GfxSemaphore>> m_waitSems;
		Vector<Ref<GfxFence>> m_fences;

		u32 m_prevIndex = 0;
		u32 m_currIndex = 0;

		b8 m_frameCompleted = true;
	};
}
