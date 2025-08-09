/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Queue/GfxQueue.h>

#include <vulkan/vulkan.h>

namespace Strand
{
	class GfxVkQueue final : public GfxQueue
	{
		friend class GfxVkDevice;

	public:
		GfxVkQueue(const GfxQueueDesc& desc, GfxDevice* pDevice);
		~GfxVkQueue() override;

		void* Queue() const override final;
		void Submit(const Vector<GfxCommandBuffer*>& cmdBuffers, const Vector<GfxSemaphore*>& waits,
			const Vector<GfxSemaphore*>& signals, const GfxFence* fence, PipelineStageFlags flags) const override final;
		void WaitIdle() const override final;

	private:
		VkQueue m_queue;
	};
}
