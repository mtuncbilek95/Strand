#include "VDescriptorPool.h"

#include <Runtime/Vulkan/Debug/VDebug.h>
#include <Runtime/Vulkan/Device/VDevice.h>

namespace Flax
{
	VDescPool::VDescPool(const DescPoolProps& desc, VDevice* pDevice) : VObject(pDevice), m_props(desc)
	{
		VkDescriptorPoolCreateInfo poolInfo = { VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO };
		poolInfo.maxSets = desc.maxSets;
		poolInfo.flags = desc.createFlag;
		poolInfo.poolSizeCount = static_cast<u32>(desc.poolSizes.size());
		poolInfo.pPoolSizes = desc.poolSizes.data();

		VDebug::VkAssert(vkCreateDescriptorPool(m_rootDevice->GetVkDevice(), &poolInfo, nullptr, &m_pool), "VDescPool");
	}

	VDescPool::~VDescPool()
	{
        if (m_pool != VK_NULL_HANDLE)
        {
            vkDestroyDescriptorPool(m_rootDevice->GetVkDevice(), m_pool, nullptr);
            m_pool = VK_NULL_HANDLE;
        }
	}
}