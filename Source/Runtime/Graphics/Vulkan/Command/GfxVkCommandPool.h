/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Command/GfxCommandPool.h>

#include <vulkan/vulkan.h>

namespace Flax
{
	class GfxVkCommandPool : public GfxCommandPool
	{
	public:
		GfxVkCommandPool(const GfxCommandPoolDesc& desc, GfxDevice* pDevice);
		~GfxVkCommandPool() override final;

		void* Pool() const override final;
		Ref<GfxCommandBuffer> CreateBuffer(CommandLevel lvl) override final;

	private:
		VkCommandPool m_pool;
	};
}
