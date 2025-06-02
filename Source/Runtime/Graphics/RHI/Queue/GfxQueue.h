/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Object/GfxObject.h>
#include <Runtime/Graphics/RHI/Queue/GfxQueueDesc.h>
#include <Runtime/Graphics/RHI/Util/PipelineStageFlags.h>

namespace Flax
{
	class GfxCommandBuffer;
	class GfxFence;
	class GfxSemaphore;

	class GfxQueue : public GfxObject
	{
	public:
		GfxQueue(const GfxQueueDesc& desc, GfxDevice* pDevice);
		virtual ~GfxQueue() override = default;

		virtual void* Queue() const = 0;
		virtual void Submit(const Vector<GfxCommandBuffer*>& cmdBuffers, const Vector<GfxSemaphore*>& waits, 
			const Vector<GfxSemaphore*>& signals, const GfxFence* fence, PipelineStageFlags flags) const = 0;
		virtual void WaitIdle() const = 0;

		QueueType Type() const { return m_desc.type; }
		u32 FamilyIndex() const { return m_desc.familyIndex; }

	private:
		GfxQueueDesc m_desc;
	};
}
