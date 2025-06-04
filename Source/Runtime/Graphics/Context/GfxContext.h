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

	class GfxContext : public Singleton<GfxContext>
	{
	public:
		void CreateContext(const GfxContextDesc& desc);

		GfxInstance* Instance() const { return m_instance.get(); }
		GfxDevice* Device() const { return m_device.get(); }
		GfxQueue* GraphicsQueue() const { return m_graphicsQueue.get(); }
		GfxQueue* TransferQueue() const { return m_transferQueue.get(); }
		GfxQueue* ComputeQueue() const { return m_computeQueue.get(); }

	private:
		Ref<GfxInstance> m_instance;
		Ref<GfxDevice> m_device;
		
		Ref<GfxQueue> m_graphicsQueue;
		Ref<GfxQueue> m_computeQueue;
		Ref<GfxQueue> m_transferQueue;

		Ref<GfxSwapchain> m_swapchain;

		Ref<GfxCommandPool> m_cmdPool;
		Vector<Ref<GfxCommandBuffer>> m_cmdBuffers;
	};
}
