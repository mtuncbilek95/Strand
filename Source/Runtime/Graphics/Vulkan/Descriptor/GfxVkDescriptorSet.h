/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Descriptor/GfxDescriptorSet.h>

#include <vulkan/vulkan.h >

namespace Strand
{
	class GfxVkDescriptorSet : public GfxDescriptorSet
	{
	public:
		GfxVkDescriptorSet(const GfxDescriptorSetDesc& desc, GfxDevice* pDevice);
		~GfxVkDescriptorSet() override final;

		void* DescSet() const override final;
		void Update(const GfxSetUpdateDesc& update) const override final;

	private:
		VkDescriptorSet m_set;
	};
}
