/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Descriptor/GfxDescriptorPool.h>

#include <vulkan/vulkan.h>

namespace Strand
{
	class GfxVkDescriptorPool final : public GfxDescriptorPool
	{
	public:
		GfxVkDescriptorPool(const GfxDescriptorPoolDesc& desc, GfxDevice* pDevice);
		~GfxVkDescriptorPool() override final;

		void* DescPool() const override final;

	private:
		VkDescriptorPool m_pool;
	};
}
