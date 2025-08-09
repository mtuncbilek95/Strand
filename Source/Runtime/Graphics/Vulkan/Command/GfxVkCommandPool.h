/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Command/GfxCommandPool.h>

#include <vulkan/vulkan.h>

namespace Strand
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
