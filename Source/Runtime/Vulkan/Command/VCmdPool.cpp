#include "VCmdPool.h"

#include <Runtime/Vulkan/Debug/VDebug.h>
#include <Runtime/Vulkan/Device/VDevice.h>
#include <Runtime/Vulkan/Queue/VQueue.h>
#include <Runtime/Vulkan/Command/VCmdBuffer.h>

namespace Flax
{
	VCmdPool::VCmdPool(const CmdPoolProps& desc, VDevice* pDevice) : VObject(pDevice),
		m_props(desc), m_cmdPool(VK_NULL_HANDLE)
	{
		VkCommandPoolCreateInfo poolInfo = { VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO };
		poolInfo.queueFamilyIndex = desc.queue->GetFamilyIndex();
		poolInfo.flags = desc.flags;

		VDebug::VkAssert(vkCreateCommandPool(GetRoot()->GetVkDevice(), &poolInfo, nullptr, &m_cmdPool), "VCmdPool");
	}

	VCmdPool::~VCmdPool()
	{
		if (m_cmdPool != VK_NULL_HANDLE)
		{
			vkDestroyCommandPool(GetRoot()->GetVkDevice(), m_cmdPool, nullptr);
			m_cmdPool = VK_NULL_HANDLE;
		}
	}

	Ref<VCmdBuffer> VCmdPool::CreateCmdBuffer(VkCommandBufferLevel cmdLevel)
	{
		CmdBufferProps prop =
		{
			.cmdLevel = cmdLevel,
			.pool = this
		};
		return NewRef<VCmdBuffer>(prop, GetRoot());
	}
}