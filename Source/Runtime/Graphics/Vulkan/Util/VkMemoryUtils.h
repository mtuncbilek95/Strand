/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Util/MemoryFormat.h>

#include <vulkan/vulkan.h>
#include <vma/vk_mem_alloc.h>

namespace Flax
{
	struct VmaUtils
	{
		static VmaMemoryUsage GetVmaUsage(MemoryUsage usage);
		static VmaAllocationCreateFlags GetVmaFlags(MemoryAllocation alloc);
	};
}
