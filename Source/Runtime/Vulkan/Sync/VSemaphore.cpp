#include "VSemaphore.h"

#include <Runtime/Vulkan/Debug/VDebug.h>
#include <Runtime/Vulkan/Device/VDevice.h>

namespace Flax
{
	VSemaphore::VSemaphore(VDevice* pDevice) : VObject(pDevice)
	{
		VkSemaphoreCreateInfo semaphoreInfo = { VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO };
		VDebug::VkAssert(vkCreateSemaphore(m_rootDevice->GetVkDevice(), &semaphoreInfo, nullptr, &m_semaphore), "VSemaphore");
	}

	VSemaphore::~VSemaphore()
	{
        if (m_semaphore != VK_NULL_HANDLE)
        {
            vkDestroySemaphore(m_rootDevice->GetVkDevice(), m_semaphore, nullptr);
            m_semaphore = VK_NULL_HANDLE;
        }
	}
}