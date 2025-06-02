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
#include <Runtime/Graphics/RHI/Sync/GfxFence.h>

#include <vulkan/vulkan.h>

namespace Flax
{
	class GfxVkFence : public GfxFence
	{
	public:
		GfxVkFence(const GfxFenceDesc& desc, GfxDevice* pDevice);
		~GfxVkFence() override final;

		void* Fence() const override final;
		void WaitIdle() const override final;
		void Reset() const override final;

	private:
		VkFence m_fence;
	};
}
