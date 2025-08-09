/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Util/DescriptorFormat.h>

#include <vulkan/vulkan.h>

namespace Strand
{
	struct VkDescriptorUtils
	{
		static VkDescriptorType GetVkDescType(DescriptorType type);
		static VkDescriptorPoolCreateFlags GetVkDescPoolFlags(DescriptorPoolFlags flags);
		static VkDescriptorSetLayoutCreateFlags GetVkDescLayoutFlags(DescriptorLayoutFlags flags);
	};
}