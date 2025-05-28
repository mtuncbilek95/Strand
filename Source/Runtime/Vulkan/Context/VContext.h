/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>

namespace Flax
{
	class VInstance;
	class VDevice;
	class VSwapchain;
	class VQueue;
	class VPipeline;
	class VRenderPass;

	class VContext : public Singleton<VContext>
	{
		friend class Application;
	public:
		VInstance* Instance() const { return m_vInstance.get(); }
		VDevice* Device() const { return m_vDevice.get(); }
		VSwapchain* Swapchain() const { return m_vSwapchain.get(); }
		VQueue* GraphicsQueue() const { return m_vGraphicsQueue.get(); }
		VQueue* TransferQueue() const { return m_vTransferQueue.get(); }
		VQueue* ComputeQueue() const { return m_vComputeQueue.get(); }

	private:
		VContext* Initialize();
		void Destroy();

	private:
		Ref<VInstance> m_vInstance;
		Ref<VDevice> m_vDevice;
		Ref<VSwapchain> m_vSwapchain;
		Ref<VQueue> m_vGraphicsQueue;
		Ref<VQueue> m_vTransferQueue;
		Ref<VQueue> m_vComputeQueue;
	};
}
