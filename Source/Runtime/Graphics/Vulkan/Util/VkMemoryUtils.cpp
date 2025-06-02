#include "VkMemoryUtils.h"

#include <magic_enum.hpp>

namespace Flax
{
	VmaMemoryUsage VmaUtils::GetVmaUsage(MemoryUsage usage)
	{
		VmaMemoryUsage flags;

		for (auto u : magic_enum::enum_values<MemoryUsage>())
		{
			if (HasFlag(usage, u))
			{

			}
		}
		return VmaMemoryUsage();
	}

	VmaAllocationCreateFlags VmaUtils::GetVmaFlags(MemoryAllocation alloc)
	{
		return VmaAllocationCreateFlags();
	}
}
