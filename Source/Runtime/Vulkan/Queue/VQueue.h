/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Vulkan/Object/VObject.h>

namespace Flax
{
	struct QueueProps final
	{
		u32 familyIndex;
		VkQueueFlags flags;
		VkQueue queue;
	};

	class VQueue final : public VObject
	{
	public:
		VQueue(const QueueProps& desc, VDevice* pDevice);
		~VQueue() override final;

		void WaitQueueIdle() const;
		void Submit(const Vector<VCmdBuffer*>& cmds, const Vector<VSemaphore*>& waits, const Vector<VSemaphore*>& signals, VFence* fence, VkPipelineStageFlags flags) const;

		inline VkQueue GetVkQueue() const { return m_props.queue; }
		inline u32 GetFamilyIndex() const { return m_props.familyIndex; }
		inline VkQueueFlags GetFlags() const { return m_props.flags; }

	private:
		QueueProps m_props;
	};
}