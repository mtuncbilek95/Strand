#include "VLoader.h"

PFN_vkCreateDebugUtilsMessengerEXT debugMessengerCreateProc = nullptr;
PFN_vkDestroyDebugUtilsMessengerEXT debugMessengerDestroyProc = nullptr;

namespace Flax
{
	void LoadInstanceFunctions(VkInstance instance)
	{
		debugMessengerCreateProc = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT"));
		debugMessengerDestroyProc = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT"));
	}

	void LoadDeviceFunctions(VkDevice device)
	{
	}
}