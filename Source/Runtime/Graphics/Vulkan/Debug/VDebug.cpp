#include "VDebug.h"

#define VMA_IMPLEMENTATION
#include <vma/vk_mem_alloc.h>

#define VOLK_IMPLEMENTATION
#include <volk/volk.h>

#include <magic_enum/magic_enum.hpp>

namespace Flax
{
	void VDebug::VkAssert(VkResult result, const String& objectTitle)
	{
		if (result != VK_SUCCESS && result != VK_ERROR_DEVICE_LOST && result != VK_ERROR_INITIALIZATION_FAILED)
			Log::Error(LogType::GraphicsAPI, "{0} - {1}", objectTitle, magic_enum::enum_name<VkResult>(result));

		if(result == VK_ERROR_DEVICE_LOST || result == VK_ERROR_INITIALIZATION_FAILED)
			Log::Critical(LogType::GraphicsAPI, "{0} - {1}", objectTitle, magic_enum::enum_name<VkResult>(result));
	}
}