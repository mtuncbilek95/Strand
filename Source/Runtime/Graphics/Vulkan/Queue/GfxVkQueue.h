/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Queue/GfxQueue.h>

#include <vulkan/vulkan.h>

namespace Flax
{
	class GfxVkQueue final : public GfxQueue
	{
		friend class GfxVkDevice;

	public:
		GfxVkQueue(const GfxQueueDesc& desc, GfxDevice* pDevice);
		~GfxVkQueue() override;

		void* Queue() const override final;
		void Submit(const Vector<GfxCommandBuffer*>& cmdBuffers, const Vector<GfxSemaphore*>& waits,
			const Vector<GfxSemaphore*>& signals, const GfxFence* fence, PipelineStageFlags flags) const override final {}
		void WaitIdle() const override final;

	private:
		GfxQueueDesc m_desc;

		VkQueue m_queue;
	};
}
