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
	struct BindingProps final
	{
		u32 binding;
		VkDescriptorType type;
		u32 count;
		VkShaderStageFlags stageFlags;
	};

	struct DescLayoutProps final
	{
		Vector<BindingProps> bindings;
		VkDescriptorSetLayoutCreateFlags createFlags;
	};

	class VDescLayout final : public VObject
	{
	public:
		VDescLayout(const DescLayoutProps& desc, VDevice* pDevice);
		~VDescLayout() override final;

		inline VkDescriptorSetLayout GetVkLayout() const { return m_layout; }

	private:
		DescLayoutProps m_props;

		VkDescriptorSetLayout m_layout;
	};
}