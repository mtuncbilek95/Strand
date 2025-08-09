/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Util/MemoryFormat.h>

#include <vulkan/vulkan.h>
#include <vma/vk_mem_alloc.h>

namespace Strand
{
	struct VmaUtils
	{
		static VmaMemoryUsage GetVmaUsage(MemoryUsage usage);
		static VmaAllocationCreateFlags GetVmaFlags(MemoryAllocation alloc);
	};
}
