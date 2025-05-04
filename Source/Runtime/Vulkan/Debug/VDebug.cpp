#include "VDebug.h"

#define VMA_IMPLEMENTATION
#include <vma/vk_mem_alloc.h>

#include <magic_enum.hpp>

namespace Flax
{
	void VDebug::VkAssert(VkResult result, const String& objectTitle)
	{
		if (result != VK_SUCCESS)
		{
            Log::Error(LogType::Render, "{0} - {1}", objectTitle, magic_enum::enum_name<VkResult>(result));
			exit(result);
		}
	}
}
