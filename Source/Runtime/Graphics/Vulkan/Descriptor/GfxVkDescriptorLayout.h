/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Descriptor/GfxDescriptorLayout.h>

#include <vulkan/vulkan.h>

namespace Strand
{
	class GfxVkDescriptorLayout : public GfxDescriptorLayout
	{
	public:
		GfxVkDescriptorLayout(const GfxDescriptorLayoutDesc& desc, GfxDevice* pDevice);
		~GfxVkDescriptorLayout() override final;

		void* DescLayout() const override final;

	private:
		VkDescriptorSetLayout m_layout;
	};
}
