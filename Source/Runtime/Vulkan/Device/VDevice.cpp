#include "VDevice.h"

#include <Runtime/Vulkan/Debug/VDebug.h>
#include <Runtime/Vulkan/Instance/VInstance.h>
#include <Runtime/Vulkan/Queue/VQueue.h>

namespace Flax
{
	VkQueue VDevice::QueueFamily::GetFreeQueue()
	{
		if (m_queueCount > 0)
		{
			VkQueue queue = m_queues.back();
			m_queues.pop_back();
			m_queueCount--;
			return queue;
		}

		return VK_NULL_HANDLE;
	}

	void VDevice::QueueFamily::FillQueues(VkDevice device)
	{
		for (u32 i = 0; i < m_requestedCount; i++)
		{
			VkQueue queue;
			vkGetDeviceQueue(device, m_familyIndex, i, &queue);
			m_queues.push_back(queue);
		}
	}

	VDevice::VDevice(const DeviceProps& desc, VInstance* pInstance) : m_props(desc), m_device(VK_NULL_HANDLE)
		, m_adapter(pInstance->GetVkAdapter()), m_instance(pInstance->GetVkInstance())
	{
		u32 queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(m_adapter, &queueFamilyCount, nullptr);

		Vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(m_adapter, &queueFamilyCount, queueFamilies.data());

		i32 index = 0;
		for (auto& prop : queueFamilies)
		{
			if (prop.queueFlags & VK_QUEUE_GRAPHICS_BIT && m_graphicsQueueFamily.m_familyIndex == 255)
			{
				m_graphicsQueueFamily.m_familyIndex = index;
				m_graphicsQueueFamily.m_queueCount = prop.queueCount;
				m_graphicsQueueFamily.m_requestedCount = m_graphicsQueueFamily.m_requestedCount > prop.queueCount ? prop.queueCount :
					desc.gQueueCount;
			}
			else if (prop.queueFlags & VK_QUEUE_COMPUTE_BIT && m_computeQueueFamily.m_familyIndex == 255)
			{
				m_computeQueueFamily.m_familyIndex = index;
				m_computeQueueFamily.m_queueCount = prop.queueCount;
				m_computeQueueFamily.m_requestedCount = m_computeQueueFamily.m_requestedCount > prop.queueCount ? prop.queueCount :
					desc.cQueueCount;
			}
			else if (prop.queueFlags & VK_QUEUE_TRANSFER_BIT && m_transferQueueFamily.m_familyIndex == 255)
			{
				m_transferQueueFamily.m_familyIndex = index;
				m_transferQueueFamily.m_queueCount = prop.queueCount;
				m_transferQueueFamily.m_requestedCount = m_transferQueueFamily.m_requestedCount > prop.queueCount ? prop.queueCount :
					desc.tQueueCount;
			}
			else if (prop.queueFlags & VK_QUEUE_SPARSE_BINDING_BIT && m_transferQueueFamily.m_familyIndex == 255)
			{
				m_sparseQueueFamily.m_familyIndex = index;
				m_sparseQueueFamily.m_queueCount = prop.queueCount;
				m_sparseQueueFamily.m_requestedCount = m_transferQueueFamily.m_requestedCount > prop.queueCount ? prop.queueCount :
					desc.tQueueCount;
			}
			index++;
		}

		Vector<f32> queuePriorities(16, 1.0f);
		Vector<VkDeviceQueueCreateInfo> queueCreateInfos;

		if (m_graphicsQueueFamily.m_familyIndex != 255)
		{
			VkDeviceQueueCreateInfo queueCreateInfo = {};
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueFamilyIndex = m_graphicsQueueFamily.m_familyIndex;
			queueCreateInfo.queueCount = m_graphicsQueueFamily.m_requestedCount;
			queueCreateInfo.pQueuePriorities = queuePriorities.data();
			queueCreateInfos.push_back(queueCreateInfo);
		}

		if (m_computeQueueFamily.m_familyIndex != 255)
		{
			VkDeviceQueueCreateInfo queueCreateInfo = {};
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueFamilyIndex = m_computeQueueFamily.m_familyIndex;
			queueCreateInfo.queueCount = m_computeQueueFamily.m_requestedCount;
			queueCreateInfo.pQueuePriorities = queuePriorities.data();
			queueCreateInfos.push_back(queueCreateInfo);
		}

		if (m_transferQueueFamily.m_familyIndex != 255)
		{
			VkDeviceQueueCreateInfo queueCreateInfo = {};
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueFamilyIndex = m_transferQueueFamily.m_familyIndex;
			queueCreateInfo.queueCount = m_transferQueueFamily.m_requestedCount;
			queueCreateInfo.pQueuePriorities = queuePriorities.data();
			queueCreateInfos.push_back(queueCreateInfo);
		}

		if (m_sparseQueueFamily.m_familyIndex != 255)
		{
			VkDeviceQueueCreateInfo queueCreateInfo = {};
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueFamilyIndex = m_sparseQueueFamily.m_familyIndex;
			queueCreateInfo.queueCount = m_sparseQueueFamily.m_requestedCount;
			queueCreateInfo.pQueuePriorities = queuePriorities.data();
			queueCreateInfos.push_back(queueCreateInfo);
		}

		struct ExtensionEntry
		{
			const char* name;
			b8 supported;
		};

		Vector<ExtensionEntry> extensions;
		Vector<const char*> workingExtensions;
		extensions.push_back({ VK_KHR_SWAPCHAIN_EXTENSION_NAME, false });

		//Check if the device supports the extensions
		u32 extensionCount = 0;
		vkEnumerateDeviceExtensionProperties(m_adapter, nullptr, &extensionCount, nullptr);
		Vector<VkExtensionProperties> availableExtensions(extensionCount);
		vkEnumerateDeviceExtensionProperties(m_adapter, nullptr, &extensionCount, availableExtensions.data());

		for (usize i = 0; i < extensions.size(); ++i)
		{
			for (auto& extension : availableExtensions)
			{
				if (strcmp(extensions[i].name, extension.extensionName) == 0)
				{
					extensions[i].supported = true;
					workingExtensions.push_back(extensions[i].name);
					break;
				}
			}
		}

		for (auto& extension : extensions)
			if (extension.supported)
				workingExtensions.push_back(extension.name);

		VkPhysicalDeviceFeatures deviceFeatures;
		vkGetPhysicalDeviceFeatures(m_adapter, &deviceFeatures);

		VkDeviceCreateInfo deviceCreateInfo = {};
		deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();
		deviceCreateInfo.queueCreateInfoCount = static_cast<u32>(queueCreateInfos.size());
		deviceCreateInfo.pEnabledFeatures = &deviceFeatures;
		deviceCreateInfo.enabledExtensionCount = static_cast<u32>(workingExtensions.size());
		deviceCreateInfo.ppEnabledExtensionNames = workingExtensions.data();

		VDebug::VkAssert(vkCreateDevice(m_adapter, &deviceCreateInfo, nullptr, &m_device), "VDevice");
		volkLoadDevice(m_device);

		m_graphicsQueueFamily.FillQueues(m_device);
		m_computeQueueFamily.FillQueues(m_device);
		m_transferQueueFamily.FillQueues(m_device);
		m_sparseQueueFamily.FillQueues(m_device);

		VmaVulkanFunctions vulkanFunctions = {};
		vulkanFunctions.vkGetInstanceProcAddr = reinterpret_cast<PFN_vkGetInstanceProcAddr>(vkGetInstanceProcAddr);
		vulkanFunctions.vkGetDeviceProcAddr = reinterpret_cast<PFN_vkGetDeviceProcAddr>(vkGetDeviceProcAddr);

		VmaAllocatorCreateInfo allocatorInfo = {};
		allocatorInfo.vulkanApiVersion = VK_API_VERSION_1_4;
		allocatorInfo.physicalDevice = m_adapter;
		allocatorInfo.device = m_device;
		allocatorInfo.instance = m_instance;
		allocatorInfo.pVulkanFunctions = &vulkanFunctions;

		VDebug::VkAssert(vmaCreateAllocator(&allocatorInfo, &m_allocator), "VDevice::VMA");
	}

	VDevice::~VDevice()
	{
		if (m_allocator != VK_NULL_HANDLE)
		{
			vmaDestroyAllocator(m_allocator);
			m_allocator = VK_NULL_HANDLE;
		}

		if (m_device != VK_NULL_HANDLE)
		{
			vkDestroyDevice(m_device, nullptr);
			m_device = VK_NULL_HANDLE;
		}
	}

	Ref<VQueue> VDevice::CreateQueue(VkQueueFlags type)
	{
		QueueProps props = {};
		props.flags = type;

		switch (type)
		{
		case VK_QUEUE_GRAPHICS_BIT:
		{
			props.familyIndex = m_graphicsQueueFamily.m_familyIndex;
			props.queue = m_graphicsQueueFamily.GetFreeQueue();
			break;
		}
		case VK_QUEUE_COMPUTE_BIT:
		{
			props.familyIndex = m_computeQueueFamily.m_familyIndex;
			props.queue = m_computeQueueFamily.GetFreeQueue();
			break;
		}
		case VK_QUEUE_TRANSFER_BIT:
		{
			props.familyIndex = m_transferQueueFamily.m_familyIndex;
			props.queue = m_transferQueueFamily.GetFreeQueue();
			break;
		}
		case VK_QUEUE_SPARSE_BINDING_BIT:
		{
			props.familyIndex = m_sparseQueueFamily.m_familyIndex;
			props.queue = m_sparseQueueFamily.GetFreeQueue();
			break;
		}
		default:
			Log::Critical(LogType::GraphicsAPI, "Vulkan: Unknown queue type requested.");
			return nullptr;
		}

		return NewRef<VQueue>(props, this);
	}

	void VDevice::WaitDeviceIdle() const
	{
		VDebug::VkAssert(vkDeviceWaitIdle(m_device), "VDevice");
	}
}