#include "VCmdBuffer.h"

#include <Runtime/Vulkan/Debug/VDebug.h>
#include <Runtime/Vulkan/Device/VDevice.h>
#include <Runtime/Vulkan/Command/VCmdPool.h>

namespace Flax
{
	VCmdBuffer::VCmdBuffer(const CmdBufferProps& desc, VDevice* pDevice) : VObject(pDevice), m_props(desc), 
		m_buffer(VK_NULL_HANDLE)
	{
		VkCommandBufferAllocateInfo allocInfo = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO };
		allocInfo.commandPool = desc.pool->GetVkCmdPool();
		allocInfo.level = desc.cmdLevel;
		allocInfo.commandBufferCount = 1;

		VDebug::VkAssert(vkAllocateCommandBuffers(GetRoot()->GetVkDevice(), &allocInfo, &m_buffer), "VCmdBuffer");
	}

	VCmdBuffer::~VCmdBuffer()
	{
		if (m_buffer != VK_NULL_HANDLE)
		{
			vkFreeCommandBuffers(GetRoot()->GetVkDevice(), m_props.pool->GetVkCmdPool(), 1, &m_buffer);
			m_buffer = VK_NULL_HANDLE;
		}
	}

	void VCmdBuffer::BeginRecord(VkCommandBufferUsageFlags flags) const
	{
		vkResetCommandBuffer(m_buffer, VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT);

		VkCommandBufferBeginInfo info = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO };
		info.flags = flags;

		VDebug::VkAssert(vkBeginCommandBuffer(m_buffer, &info), "VCmdBUffer");
	}

	void VCmdBuffer::EndRecord() const
	{
		vkEndCommandBuffer(m_buffer);
	}

	void VCmdBuffer::BeginRenderPass(const RenderPassBeginParams& params)
	{
	}

	void VCmdBuffer::EndRenderPass()
	{
	}
}