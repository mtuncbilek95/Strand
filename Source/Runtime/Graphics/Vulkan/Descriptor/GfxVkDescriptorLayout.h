/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Descriptor/GfxDescriptorLayout.h>

#include <vulkan/vulkan.h>

namespace Flax
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
