#include "GfxVkDevice.h"

#include <Runtime/Graphics/Vulkan/Debug/VDebug.h>

#include <Runtime/Graphics/Vulkan/Instance/GfxVkInstance.h>
#include <Runtime/Graphics/Vulkan/Queue/GfxVkQueue.h>
#include <Runtime/Graphics/Vulkan/Image/GfxVkImage.h>
#include <Runtime/Graphics/Vulkan/Image/GfxVkImageView.h>
#include <Runtime/Graphics/Vulkan/Swapchain/GfxVkSwapchain.h>
#include <Runtime/Graphics/Vulkan/Shader/GfxVkShader.h>
#include <Runtime/Graphics/Vulkan/Sampler/GfxVkSampler.h>
#include <Runtime/Graphics/Vulkan/Sync/GfxVkFence.h>
#include <Runtime/Graphics/Vulkan/Sync/GfxVkSemaphore.h>
#include <Runtime/Graphics/Vulkan/Buffer/GfxVkBuffer.h>
#include <Runtime/Graphics/Vulkan/Pipeline/GfxVkPipeline.h>
#include <Runtime/Graphics/Vulkan/Command/GfxVkCommandBuffer.h>
#include <Runtime/Graphics/Vulkan/Command/GfxVkCommandPool.h>
#include <Runtime/Graphics/Vulkan/Descriptor/GfxVkDescriptorLayout.h>
#include <Runtime/Graphics/Vulkan/Descriptor/GfxVkDescriptorPool.h>
#include <Runtime/Graphics/Vulkan/Descriptor/GfxVkDescriptorSet.h>
#include <Runtime/Graphics/Vulkan/Framebuffer/GfxVkFramebuffer.h>
#include <Runtime/Graphics/Vulkan/RenderPass/GfxVkRenderPass.h>

namespace Flax
{
	VkQueue GfxVkDevice::QueueFamily::GetFreeQueue()
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

	void GfxVkDevice::QueueFamily::FillQueues(VkDevice device)
	{
		for (u32 i = 0; i < m_requestedCount; i++)
		{
			VkQueue queue;
			vkGetDeviceQueue(device, m_familyIndex, i, &queue);
			m_queues.push_back(queue);
		}
	}

	GfxVkDevice::GfxVkDevice(const GfxDeviceDesc& desc, GfxInstance* pInstance) : GfxDevice(desc, pInstance)
	{
		m_instance = static_cast<VkInstance>(pInstance->Instance());
		m_adapter = static_cast<VkPhysicalDevice>(pInstance->Adapter());

		u32 queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(m_adapter, &queueFamilyCount, nullptr);

		Vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(m_adapter, &queueFamilyCount, queueFamilies.data());

		i32 index = 0;
		for (auto& prop : queueFamilies)
		{
			if (prop.queueFlags & VK_QUEUE_GRAPHICS_BIT && m_graphicsQueue.m_familyIndex == 255)
			{
				m_graphicsQueue.m_familyIndex = index;
				m_graphicsQueue.m_queueCount = prop.queueCount;
				m_graphicsQueue.m_requestedCount = m_graphicsQueue.m_requestedCount > prop.queueCount ? prop.queueCount :
					desc.graphicsQueueCount;
			}
			else if (prop.queueFlags & VK_QUEUE_COMPUTE_BIT && m_computeQueue.m_familyIndex == 255)
			{
				m_computeQueue.m_familyIndex = index;
				m_computeQueue.m_queueCount = prop.queueCount;
				m_computeQueue.m_requestedCount = m_computeQueue.m_requestedCount > prop.queueCount ? prop.queueCount :
					desc.computeQueueCount;
			}
			else if (prop.queueFlags & VK_QUEUE_TRANSFER_BIT && m_transferQueue.m_familyIndex == 255)
			{
				m_transferQueue.m_familyIndex = index;
				m_transferQueue.m_queueCount = prop.queueCount;
				m_transferQueue.m_requestedCount = m_transferQueue.m_requestedCount > prop.queueCount ? prop.queueCount :
					desc.transferQueueCount;
			}
			index++;
		}

		Vector<f32> queuePriorities(16, 1.0f);
		Vector<VkDeviceQueueCreateInfo> queueCreateInfos;

		if (m_graphicsQueue.m_familyIndex != 255)
		{
			VkDeviceQueueCreateInfo queueCreateInfo = {};
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueFamilyIndex = m_graphicsQueue.m_familyIndex;
			queueCreateInfo.queueCount = m_graphicsQueue.m_requestedCount;
			queueCreateInfo.pQueuePriorities = queuePriorities.data();
			queueCreateInfos.push_back(queueCreateInfo);
		}

		if (m_computeQueue.m_familyIndex != 255)
		{
			VkDeviceQueueCreateInfo queueCreateInfo = {};
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueFamilyIndex = m_computeQueue.m_familyIndex;
			queueCreateInfo.queueCount = m_computeQueue.m_requestedCount;
			queueCreateInfo.pQueuePriorities = queuePriorities.data();
			queueCreateInfos.push_back(queueCreateInfo);
		}

		if (m_transferQueue.m_familyIndex != 255)
		{
			VkDeviceQueueCreateInfo queueCreateInfo = {};
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueFamilyIndex = m_transferQueue.m_familyIndex;
			queueCreateInfo.queueCount = m_transferQueue.m_requestedCount;
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
		extensions.push_back({ VK_KHR_MAINTENANCE3_EXTENSION_NAME, false });
		extensions.push_back({ VK_KHR_MAINTENANCE_5_EXTENSION_NAME, false });
		extensions.push_back({ VK_KHR_DYNAMIC_RENDERING_EXTENSION_NAME, false });

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

		VkPhysicalDeviceDynamicRenderingFeaturesKHR dynamicRendering = {};
		dynamicRendering.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DYNAMIC_RENDERING_FEATURES_KHR;
		dynamicRendering.dynamicRendering = VK_TRUE;

		VkPhysicalDeviceFeatures deviceFeatures;
		vkGetPhysicalDeviceFeatures(m_adapter, &deviceFeatures);

		VkDeviceCreateInfo deviceCreateInfo = {};
		deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();
		deviceCreateInfo.queueCreateInfoCount = static_cast<u32>(queueCreateInfos.size());
		deviceCreateInfo.pEnabledFeatures = &deviceFeatures;
		deviceCreateInfo.enabledExtensionCount = static_cast<u32>(workingExtensions.size());
		deviceCreateInfo.ppEnabledExtensionNames = workingExtensions.data();
		deviceCreateInfo.pNext = &dynamicRendering;

		VDebug::VkAssert(vkCreateDevice(m_adapter, &deviceCreateInfo, nullptr, &m_device), "GfxVkDevice");
		volkLoadDevice(m_device);

		m_graphicsQueue.FillQueues(m_device);
		m_computeQueue.FillQueues(m_device);
		m_transferQueue.FillQueues(m_device);

		VmaVulkanFunctions vulkanFunctions = {};
		vulkanFunctions.vkGetInstanceProcAddr = reinterpret_cast<PFN_vkGetInstanceProcAddr>(vkGetInstanceProcAddr);
		vulkanFunctions.vkGetDeviceProcAddr = reinterpret_cast<PFN_vkGetDeviceProcAddr>(vkGetDeviceProcAddr);

		VmaAllocatorCreateInfo allocatorInfo = {};
		allocatorInfo.vulkanApiVersion = VK_API_VERSION_1_4;
		allocatorInfo.physicalDevice = m_adapter;
		allocatorInfo.device = m_device;
		allocatorInfo.instance = m_instance;
		allocatorInfo.pVulkanFunctions = &vulkanFunctions;

		VDebug::VkAssert(vmaCreateAllocator(&allocatorInfo, &m_allocator), "GfxVkDevice::VMA");
	}

	GfxVkDevice::~GfxVkDevice()
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
	
	void* GfxVkDevice::Device() const { return static_cast<void*>(m_device); }
	void* GfxVkDevice::Instance() const { return static_cast<void*>(m_instance); }
	void* GfxVkDevice::Adapter() const { return static_cast<void*>(m_adapter); }
	void* GfxVkDevice::Allocator() const { return static_cast<void*>(m_allocator); }

	void GfxVkDevice::WaitIdle() const
	{
		vkDeviceWaitIdle(m_device);
	}

	Ref<GfxQueue> GfxVkDevice::CreateQueue(QueueType type)
	{
		switch (type)
		{
		case QueueType::Graphics:
		{
			GfxQueueDesc desc = GfxQueueDesc().setType(type)
				.setIndex(m_graphicsQueue.m_familyIndex);

			Ref<GfxVkQueue> q = NewRef<GfxVkQueue>(desc, this);
			q->m_queue = m_graphicsQueue.GetFreeQueue();
			return q;
		}
		case QueueType::Transfer:
		{
			GfxQueueDesc desc = GfxQueueDesc().setType(type)
				.setIndex(m_transferQueue.m_familyIndex);

			Ref<GfxVkQueue> q = NewRef<GfxVkQueue>(desc, this);
			q->m_queue = m_transferQueue.GetFreeQueue();
			return q;
		}
		case QueueType::Compute:
		{
			GfxQueueDesc desc = GfxQueueDesc().setType(type)
				.setIndex(m_computeQueue.m_familyIndex);

			Ref<GfxVkQueue> q = NewRef<GfxVkQueue>(desc, this);
			q->m_queue = m_computeQueue.GetFreeQueue();
			return q;
		}
		case QueueType::Sparse:
		{
			Log::Critical(LogType::GraphicsAPI, "Vulkan::SparseQueue has not been implemented yet!");
			return nullptr;
		}
		default:
			Log::Critical(LogType::GraphicsAPI, "Could not find the requested queue!");
			return nullptr;
		}

		return nullptr;
	}

	Ref<GfxImage> GfxVkDevice::CreateImage(const GfxImageDesc& desc)
	{
		return NewRef<GfxVkImage>(desc, this);
	}

	Ref<GfxImageView> GfxVkDevice::CreateView(const GfxImageViewDesc& desc)
	{
		return NewRef<GfxVkImageView>(desc, this);
	}

	Ref<GfxSwapchain> GfxVkDevice::CreateSwapchain(const GfxSwapchainDesc& desc)
	{
		return NewRef<GfxVkSwapchain>(desc, this);
	}

	Ref<GfxBuffer> GfxVkDevice::CreateBuffer(const GfxBufferDesc& desc)
	{
		return NewRef<GfxVkBuffer>(desc, this);
	}

	Ref<GfxPipeline> GfxVkDevice::CreateGraphicsPipeline(const GfxGraphicsPipelineDesc& desc)
	{
		return NewRef<GfxVkPipeline>(desc, this);
	}

	Ref<GfxFence> GfxVkDevice::CreateSyncFence(const GfxFenceDesc& desc)
	{
		return NewRef<GfxVkFence>(desc, this);
	}

	Ref<GfxSemaphore> GfxVkDevice::CreateSyncSemaphore(const GfxSemaphoreDesc& desc)
	{
		return NewRef<GfxVkSemaphore>(desc, this);
	}

	Ref<GfxDescriptorLayout> GfxVkDevice::CreateDescriptorLayout(const GfxDescriptorLayoutDesc& desc)
	{
		return NewRef<GfxVkDescriptorLayout>(desc, this);
	}

	Ref<GfxDescriptorPool> GfxVkDevice::CreateDescriptorPool(const GfxDescriptorPoolDesc& desc)
	{
		return NewRef<GfxVkDescriptorPool>(desc, this);
	}

	Ref<GfxDescriptorSet> GfxVkDevice::CreateDescriptorSet(const GfxDescriptorSetDesc& desc)
	{
		return NewRef<GfxVkDescriptorSet>(desc, this);
	}

	Ref<GfxShader> GfxVkDevice::CreateShader(const GfxShaderDesc& desc)
	{
		return NewRef<GfxVkShader>(desc, this);
	}

	Ref<GfxCommandPool> GfxVkDevice::CreateCommandPool(const GfxCommandPoolDesc& desc)
	{
		return NewRef<GfxVkCommandPool>(desc, this);
	}

	Ref<GfxCommandBuffer> GfxVkDevice::CreateCommandBuffer(const GfxCommandBufferDesc& desc)
	{
		return NewRef<GfxVkCommandBuffer>(desc, this);
	}

	Ref<GfxFramebuffer> GfxVkDevice::CreateFramebuffer(const GfxFramebufferDesc& desc)
	{
		return NewRef<GfxVkFramebuffer>(desc, this);
	}

	Ref<GfxRenderPass> GfxVkDevice::CreateRenderPass(const GfxRenderPassDesc& desc)
	{
		return NewRef<GfxVkRenderPass>(desc, this);
	}

	Ref<GfxSampler> GfxVkDevice::CreateSampler(const GfxSamplerDesc& desc)
	{
		return NewRef<GfxVkSampler>(desc, this);
	}
}
