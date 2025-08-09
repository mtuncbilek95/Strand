/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Util/BufferFormat.h>

#include <vulkan/vulkan.h>

namespace Strand
{
	struct VkBufferUtils
	{
		static VkBufferUsageFlags GetVkBufferUsage(BufferUsage usage);
	};
}
