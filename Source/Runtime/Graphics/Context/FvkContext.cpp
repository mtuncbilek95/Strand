#include "FvkContext.h"

#include <Runtime/Window/WindowContext.h>

#define VMA_IMPLEMENTATION
#include <vma/vk_mem_alloc.h>

#define VOLK_IMPLEMENTATION
#include <volk/volk.h>

#include <magic_enum.hpp>

#include <Runtime/Graphics/Image/FvkImage.h>
#include <Runtime/Graphics/Image/FvkImageView.h>

namespace Flax
{
	static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData)
	{
		switch (messageSeverity)
		{
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
			Log::Info(LogType::GraphicsAPI, "{}", pCallbackData->pMessage);
			break;
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
			Log::Debug(LogType::GraphicsAPI, "{}", pCallbackData->pMessage);
			break;
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
			Log::Warn(LogType::GraphicsAPI, "{}", pCallbackData->pMessage);
			break;
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
			Log::Error(LogType::GraphicsAPI, "{}", pCallbackData->pMessage);
			break;
		default:
			break;
		}

		return false;
	}

	void FvkDebug::Assert(VkResult result, const String& target)
	{
		if (result != VK_SUCCESS && result != VK_ERROR_DEVICE_LOST && result != VK_ERROR_INITIALIZATION_FAILED)
			Log::Error(LogType::Render, "{0} - {1}", target, magic_enum::enum_name<VkResult>(result));

		if (result == VK_ERROR_DEVICE_LOST || result == VK_ERROR_INITIALIZATION_FAILED)
			Log::Critical(LogType::GraphicsAPI, "{0} - {1}", target, magic_enum::enum_name<VkResult>(result));
	}

	FvkContext::FvkContext()
	{

	}

	FvkContext::~FvkContext()
	{
	}

	void FvkContext::CreateContext()
	{
		volkInitialize();
		createInstance();
		pickAdapter();
		createDevice();
		pickQueues();
		createSurface();
		createSwapchain();
	}

	void FvkContext::createInstance()
	{
		const Vector<const char*> layers = {
		"VK_LAYER_KHRONOS_validation",
		"VK_LAYER_LUNARG_monitor",
		"VK_LAYER_LUNARG_screenshot"
		};

		Vector<const char*> extensions = {
			VK_KHR_SURFACE_EXTENSION_NAME,
			VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME,
			VK_KHR_GET_SURFACE_CAPABILITIES_2_EXTENSION_NAME
		};

#if defined(FLAX_WINDOWS)
		extensions.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
#endif

#if defined(FLAX_DEBUG)
		extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
#endif

		VkApplicationInfo appInfo = { VK_STRUCTURE_TYPE_APPLICATION_INFO };
		appInfo.pApplicationName = "FvkApp";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "FvkEngine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_4;

		VkInstanceCreateInfo createInfo = { VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO };
		createInfo.pApplicationInfo = &appInfo;
		createInfo.enabledExtensionCount = static_cast<u32>(extensions.size());
		createInfo.ppEnabledExtensionNames = extensions.data();
		createInfo.enabledLayerCount = static_cast<u32>(layers.size());
		createInfo.ppEnabledLayerNames = layers.data();

		FvkDebug::Assert(vkCreateInstance(&createInfo, nullptr, &m_instance), "FvkContext::createInstance");
		volkLoadInstance(m_instance);

#if defined(FLAX_DEBUG)
		VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = {};
		debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		debugCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		debugCreateInfo.pfnUserCallback = DebugCallback;
		debugCreateInfo.pUserData = nullptr;

		FvkDebug::Assert(vkCreateDebugUtilsMessengerEXT(m_instance, &debugCreateInfo, nullptr, &m_debugMessenger), "FvkContext::createInstance");
#endif
	}

	void FvkContext::pickAdapter()
	{
		u32 deviceCount = 0;
		FvkDebug::Assert(vkEnumeratePhysicalDevices(m_instance, &deviceCount, nullptr), "FvkContext::pickAdapter");

		// Temporary struct to hold the device and its score
		HashMap<String, Pair<VkPhysicalDevice, u32>> allDevices;

		// Get the physical devices
		Vector<VkPhysicalDevice> devices(deviceCount);
		FvkDebug::Assert(vkEnumeratePhysicalDevices(m_instance, &deviceCount, devices.data()), "FvkContext::pickAdapter");

		for (auto& device : devices)
		{
			// Get the device properties
			VkPhysicalDeviceProperties deviceProperties = {};
			vkGetPhysicalDeviceProperties(device, &deviceProperties);

			// Get the device features
			VkPhysicalDeviceFeatures deviceFeatures = {};
			vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

			// Get the device memory properties
			VkPhysicalDeviceMemoryProperties deviceMemoryProperties = {};
			vkGetPhysicalDeviceMemoryProperties(device, &deviceMemoryProperties);

			// Get the device queue family properties
			u32 queueFamilyCount = 0;
			vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

			Vector<VkQueueFamilyProperties> queueFamilyProperties(queueFamilyCount);
			vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilyProperties.data());

			// Hold device on allDevices
			allDevices[deviceProperties.deviceName] = { device, 0 };

			for (auto& queueFamily : queueFamilyProperties)
				allDevices[deviceProperties.deviceName].second += queueFamily.queueCount;

			// Check if the device is discrete
			if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
				allDevices[deviceProperties.deviceName].second += 1000;
			else
				allDevices[deviceProperties.deviceName].second += 100;

			// Check if the device supports geometry shaders
			if (deviceFeatures.geometryShader)
				allDevices[deviceProperties.deviceName].second += 10;
		}

		// Get the best device
		auto bestDevice = std::max_element(allDevices.begin(), allDevices.end(),
			[](const Pair<String, Pair<VkPhysicalDevice, u32>>& a, const Pair<String, Pair<VkPhysicalDevice, u32>>& b)
			{
				return a.second.second < b.second.second;
			});

		Log::Debug(LogType::Render, "Best device found: {}", bestDevice->first.c_str());
		m_adapter = bestDevice->second.first;
	}

	void FvkContext::createDevice()
	{
		Vector<VkQueueFamilyProperties> queueFamilies;
		u32 queueFamilyCount = 0;

		vkGetPhysicalDeviceQueueFamilyProperties(m_adapter, &queueFamilyCount, nullptr);
		queueFamilies.resize(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(m_adapter, &queueFamilyCount, queueFamilies.data());

		for (u32 i = 0; i < queueFamilyCount; ++i) {
			if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
				m_graphicsIndex = i;

			if ((queueFamilies[i].queueFlags & VK_QUEUE_TRANSFER_BIT) &&
				!(queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT))
				m_transferIndex = i;
		}

		if (m_transferIndex == -1)
			m_transferIndex = m_graphicsIndex;

		Vector<f32> queuePriorities(16, 1.0f);
		Vector<VkDeviceQueueCreateInfo> queueCreateInfos;

		u32 uniqueFamilies[2] = { m_graphicsIndex, m_transferIndex };
		u32 familyCount = (m_graphicsIndex == m_transferIndex) ? 1 : 2;

		for (u32 i = 0; i < familyCount; ++i) {
			VkDeviceQueueCreateInfo queueInfo = { VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO };
			queueInfo.queueFamilyIndex = uniqueFamilies[i];
			queueInfo.queueCount = 1;
			queueInfo.pQueuePriorities = queuePriorities.data();

			queueCreateInfos.push_back(queueInfo);
		}

		Vector<const char*> extensions;
		extensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
		extensions.push_back(VK_KHR_MAINTENANCE3_EXTENSION_NAME);
		extensions.push_back(VK_KHR_MAINTENANCE_5_EXTENSION_NAME);

		VkPhysicalDeviceFeatures deviceFeatures = {};

		VkDeviceCreateInfo createInfo = { VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO };
		createInfo.queueCreateInfoCount = static_cast<u32>(queueCreateInfos.size());
		createInfo.pQueueCreateInfos = queueCreateInfos.data();
		createInfo.pEnabledFeatures = &deviceFeatures;
		createInfo.enabledExtensionCount = static_cast<u32>(extensions.size());
		createInfo.ppEnabledExtensionNames = extensions.data();

		FvkDebug::Assert(vkCreateDevice(m_adapter, &createInfo, nullptr, &m_device), "FvkContext::createDevice");
		volkLoadDevice(m_device);

		VmaVulkanFunctions vulkanFunctions = {};
		vulkanFunctions.vkGetInstanceProcAddr = reinterpret_cast<PFN_vkGetInstanceProcAddr>(vkGetInstanceProcAddr);
		vulkanFunctions.vkGetDeviceProcAddr = reinterpret_cast<PFN_vkGetDeviceProcAddr>(vkGetDeviceProcAddr);

		VmaAllocatorCreateInfo allocatorInfo = {};
		allocatorInfo.vulkanApiVersion = VK_API_VERSION_1_4;
		allocatorInfo.physicalDevice = m_adapter;
		allocatorInfo.device = m_device;
		allocatorInfo.instance = m_instance;
		allocatorInfo.pVulkanFunctions = &vulkanFunctions;

		FvkDebug::Assert(vmaCreateAllocator(&allocatorInfo, &m_allocator), "VDevice::VMA");
	}

	void FvkContext::pickQueues()
	{
		vkGetDeviceQueue(m_device, m_graphicsIndex, 0, &m_graphicsQueue);
		vkGetDeviceQueue(m_device, m_transferIndex, 0, &m_transferQueue);
	}

	void FvkContext::createSurface()
	{
#if defined(FLAX_WINDOWS)
		VkWin32SurfaceCreateInfoKHR surfaceInfo = { VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR };
		surfaceInfo.hinstance = GetModuleHandle(nullptr);
		surfaceInfo.hwnd = (HWND)WindowContext::Get().CoreWindow()->GetHandle();
		FvkDebug::Assert(vkCreateWin32SurfaceKHR(m_instance, &surfaceInfo, nullptr, &m_surface), "VSwapchain");
#endif
	}

	void FvkContext::createSwapchain()
	{
		VkCommandPoolCreateInfo poolInfo = { VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO };
		poolInfo.queueFamilyIndex = m_graphicsIndex;
		poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
		FvkDebug::Assert(vkCreateCommandPool(m_device, &poolInfo, nullptr, &m_barrierPool), "VSwapchain");

		VkCommandBufferAllocateInfo bufferInfo = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO };
		bufferInfo.commandBufferCount = 1;
		bufferInfo.commandPool = m_barrierPool;
		bufferInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		FvkDebug::Assert(vkAllocateCommandBuffers(m_device, &bufferInfo, &m_barrierBuffer), "VSwapchain");

		VkFenceCreateInfo fenceInfo = { VK_STRUCTURE_TYPE_FENCE_CREATE_INFO };
		FvkDebug::Assert(vkCreateFence(m_device, &fenceInfo, nullptr, &m_barrierFence), "VSwapchain");

		VkSurfaceCapabilitiesKHR surfaceCap = {};
		FvkDebug::Assert(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(m_adapter, m_surface, &surfaceCap), "VSwapchain");

		u32 formatCount = 0;
		FvkDebug::Assert(vkGetPhysicalDeviceSurfaceFormatsKHR(m_adapter, m_surface, &formatCount, nullptr), "VSwapchain");
		Vector<VkSurfaceFormatKHR> formats(formatCount);
		FvkDebug::Assert(vkGetPhysicalDeviceSurfaceFormatsKHR(m_adapter, m_surface, &formatCount, formats.data()), "VSwapchain");

		u32 presentCount = 0;
		FvkDebug::Assert(vkGetPhysicalDeviceSurfacePresentModesKHR(m_adapter, m_surface, &presentCount, nullptr), "VSwapchain");
		Vector<VkPresentModeKHR> presentModes(presentCount);
		FvkDebug::Assert(vkGetPhysicalDeviceSurfacePresentModesKHR(m_adapter, m_surface, &presentCount, presentModes.data()), "VSwapchain");

		VkSwapchainCreateInfoKHR createInfo = { VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR };
		createInfo.surface = m_surface;
		createInfo.minImageCount = 2;
		createInfo.imageFormat = VK_FORMAT_R8G8B8A8_UNORM;
		createInfo.imageColorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;
		createInfo.imageExtent = { WindowContext::Get().CoreWindow()->GetSize().x, WindowContext::Get().CoreWindow()->GetSize().y };
		createInfo.imageArrayLayers = 1;
		createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
		createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		createInfo.preTransform = surfaceCap.currentTransform;
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		createInfo.presentMode = VK_PRESENT_MODE_FIFO_KHR;
		createInfo.clipped = VK_FALSE;
		createInfo.oldSwapchain = VK_NULL_HANDLE;
		FvkDebug::Assert(vkCreateSwapchainKHR(m_device, &createInfo, nullptr, &m_swapchain), "VSwapchain");

		u32 imageCount;
		FvkDebug::Assert(vkGetSwapchainImagesKHR(m_device, m_swapchain, &imageCount, nullptr), "VSwapchain");

		Vector<VkImage> images(imageCount);
		FvkDebug::Assert(vkGetSwapchainImagesKHR(m_device, m_swapchain, &imageCount, images.data()), "VSwapchain");

		for (u32 i = 0; i < imageCount; ++i)
		{
			ImageProps imageProps = {};
			imageProps.imgType = VK_IMAGE_TYPE_2D;
			imageProps.imgSize = { WindowContext::Get().CoreWindow()->GetSize().x, WindowContext::Get().CoreWindow()->GetSize().y, 1 };
			imageProps.mipLevels = 1;
			imageProps.arrayLayers = 1;
			imageProps.imgFormat = VK_FORMAT_R8G8B8A8_UNORM;
			imageProps.imgUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

			m_images.push_back(NewRef<FvkImage>(imageProps, images[i]));

			ViewProps viewProps = {};
			m_views.push_back(m_images[i]->CreateView(viewProps));

			VkCommandBufferBeginInfo beginInfo = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO };
			beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

			FvkDebug::Assert(vkResetCommandBuffer(m_barrierBuffer, 0), "VSwapchain");
			FvkDebug::Assert(vkBeginCommandBuffer(m_barrierBuffer, &beginInfo), "VSwapchain");

			VkImageMemoryBarrier barrier = { VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER };
			barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			barrier.newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
			barrier.srcAccessMask = VK_ACCESS_NONE;
			barrier.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT;
			barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			barrier.image = m_images[i]->GetVkImage();
			barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			barrier.subresourceRange.baseMipLevel = 0;
			barrier.subresourceRange.levelCount = 1;
			barrier.subresourceRange.baseArrayLayer = 0;
			barrier.subresourceRange.layerCount = 1;
			barrier.srcAccessMask = 0;
			barrier.dstAccessMask = 0;

			vkCmdPipelineBarrier(m_barrierBuffer, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, 0, 0, nullptr, 0, nullptr, 1, &barrier);

			FvkDebug::Assert(vkEndCommandBuffer(m_barrierBuffer), "VSwapchain");

			VkSubmitInfo submitInfo = { VK_STRUCTURE_TYPE_SUBMIT_INFO };
			submitInfo.commandBufferCount = 1;
			submitInfo.pCommandBuffers = &m_barrierBuffer;

			FvkDebug::Assert(vkQueueSubmit(m_graphicsQueue, 1, &submitInfo, m_barrierFence), "VSwapchain");
			FvkDebug::Assert(vkQueueWaitIdle(m_graphicsQueue), "VSwapchain");

			vkWaitForFences(m_device, 1, &m_barrierFence, VK_TRUE, u64_max);
			vkResetFences(m_device, 1, &m_barrierFence);
		}
	}
}
