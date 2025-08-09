/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Util/CommandFormat.h>

#include <vulkan/vulkan.h>

namespace Strand
{
	struct VkCommandUtils
	{
		static VkCommandPoolCreateFlags GetVkPoolFlags(CommandPoolFlags flag);
		static VkCommandBufferLevel GetVkLevel(CommandLevel lvl);
		static VkCommandBufferUsageFlags GetVkCmdUsage(CommandBufferUsage usage);
		static VkSubpassContents GetVkContent(SubpassContent ctx);
	};
}