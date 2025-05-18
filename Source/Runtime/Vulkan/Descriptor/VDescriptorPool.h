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
	struct DescPoolProps final
	{
		Vector<VkDescriptorPoolSize> poolSizes;
		u32 maxSets;
		VkDescriptorPoolCreateFlags createFlag = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
	};

	class VDescPool final : public VObject
	{
	public:
		VDescPool(const DescPoolProps& desc, VDevice* pDevice);
		~VDescPool() override final;

		inline VkDescriptorPool GetVkPool() const { return m_pool; }

	private:
		DescPoolProps m_props;

		VkDescriptorPool m_pool;
	};
}