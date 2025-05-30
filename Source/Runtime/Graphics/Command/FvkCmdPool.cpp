#include "FvkCmdPool.h"

#include <Runtime/Vulkan/Debug/VDebug.h>
#include <Runtime/Vulkan/Command/VCmdBuffer.h>

namespace Flax
{
	FvkCmdPool::FvkCmdPool(const CmdPoolProps& desc) : m_props(desc), m_cmdPool(VK_NULL_HANDLE)
	{
		VkCommandPoolCreateInfo poolInfo = { VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO };
		poolInfo.queueFamilyIndex = desc.queue->GetFamilyIndex();
		poolInfo.flags = desc.flags;

		VDebug::VkAssert(vkCreateCommandPool(GetRoot()->GetVkDevice(), &poolInfo, nullptr, &m_cmdPool), "FvkCmdPool");
	}

	FvkCmdPool::~FvkCmdPool()
	{
		if (m_cmdPool != VK_NULL_HANDLE)
		{
			vkDestroyCommandPool(GetRoot()->GetVkDevice(), m_cmdPool, nullptr);
			m_cmdPool = VK_NULL_HANDLE;
		}
	}

	Ref<VCmdBuffer> FvkCmdPool::CreateCmdBuffer(VkCommandBufferLevel cmdLevel)
	{
		CmdBufferProps prop =
		{
			.cmdLevel = cmdLevel,
			.pool = this
		};
		return NewRef<VCmdBuffer>(prop, GetRoot());
	}
}