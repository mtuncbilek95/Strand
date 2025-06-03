/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Util/DescriptorFormat.h>

#include <vulkan/vulkan.h>

namespace Flax
{
	struct VkDescriptorUtils
	{
		static VkDescriptorType GetVkDescType(DescriptorType type);
		static VkDescriptorPoolCreateFlags GetVkDescPoolFlags(DescriptorPoolFlags flags);
		static VkDescriptorSetLayoutCreateFlags GetVkDescLayoutFlags(DescriptorLayoutFlags flags);
	};
}