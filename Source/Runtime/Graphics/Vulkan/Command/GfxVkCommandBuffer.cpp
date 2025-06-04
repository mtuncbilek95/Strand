#include "GfxVkCommandBuffer.h"

#include <Runtime/Graphics/Vulkan/Debug/VDebug.h>
#include <Runtime/Graphics/Vulkan/Device/GfxVkDevice.h>
#include <Runtime/Graphics/Vulkan/Queue/GfxVkQueue.h>
#include <Runtime/Graphics/Vulkan/Command/GfxVkCommandPool.h>
#include <Runtime/Graphics/Vulkan/RenderPass/GfxVkRenderPass.h>
#include <Runtime/Graphics/Vulkan/Framebuffer/GfxVkFramebuffer.h>
#include <Runtime/Graphics/Vulkan/Buffer/GfxVkBuffer.h>
#include <Runtime/Graphics/Vulkan/Util/VkCommandUtils.h>

namespace Flax
{
	GfxVkCommandBuffer::GfxVkCommandBuffer(const GfxCommandBufferDesc& desc, GfxDevice* pDevice) : GfxCommandBuffer(desc, pDevice)
	{
		VkCommandBufferAllocateInfo allocInfo = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO };
		allocInfo.commandPool = VkCommandPool(desc.pool->Pool());
		allocInfo.level = VkCommandUtils::GetVkLevel(desc.level);
		allocInfo.commandBufferCount = 1;

		VDebug::VkAssert(vkAllocateCommandBuffers(VkDevice(Root()->Device()), &allocInfo, &m_buffer), "GfxVkCommandBuffer");
	}

	GfxVkCommandBuffer::~GfxVkCommandBuffer()
	{
		if (m_buffer != VK_NULL_HANDLE)
		{
			vkFreeCommandBuffers(VkDevice(Root()->Device()), VkCommandPool(Pool()->Pool()), 1, &m_buffer);
			m_buffer = VK_NULL_HANDLE;
		}
	}

	void* GfxVkCommandBuffer::Buffer() const { return static_cast<void*>(m_buffer); }

	void GfxVkCommandBuffer::BeginRecord(CommandBufferUsage usage) const
	{
		vkResetCommandBuffer(m_buffer, VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT);

		VkCommandBufferBeginInfo info = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO };
		info.flags = VkCommandUtils::GetVkCmdUsage(usage);
		VDebug::VkAssert(vkBeginCommandBuffer(m_buffer, &info), "GfxVkCommandBuffer::BeginRecord");
	}

	void GfxVkCommandBuffer::BeginRecord(const InheritanceDesc& desc, CommandBufferUsage usage) const
	{
		vkResetCommandBuffer(m_buffer, VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT);

		VkCommandBufferBeginInfo info = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO };
		info.flags = VkCommandUtils::GetVkCmdUsage(usage);

		VkCommandBufferInheritanceInfo inheritInfo = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO };
		if (info.flags & VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT || info.flags & VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT)
		{
			inheritInfo.renderPass = VkRenderPass(desc.renderPass->Pass());
			inheritInfo.framebuffer = desc.framebuffer ? VkFramebuffer(desc.framebuffer->Framebuffer(desc.frameIndex)) : VK_NULL_HANDLE;
			inheritInfo.subpass = desc.subpass;
			inheritInfo.occlusionQueryEnable = false;

			info.pInheritanceInfo = &inheritInfo;
		}

		VDebug::VkAssert(vkBeginCommandBuffer(m_buffer, &info), "GfxVkCommandBuffer::BeginRecord_Inheritance");
	}

	void GfxVkCommandBuffer::EndRecord() const
	{
		vkEndCommandBuffer(m_buffer);
	}

	void GfxVkCommandBuffer::BeginRenderPass(const BeginRenderDesc& desc) const
	{
		u32 count = 0;
		count += desc.clearColor ? 1 : 0;
		count += desc.clearDepth ? 1 : 0;

		Vector<VkClearValue> clears(count);
		for (usize i = 0; i < clears.size(); i++)
		{
			if (i == 0)
				clears[i].color = { desc.colorVal.x, desc.colorVal.y , desc.colorVal.z, desc.colorVal.w };
			else
				clears[i].depthStencil = { desc.depthVal.x, static_cast<u32>(desc.depthVal.y) };
		}

		VkRenderPassBeginInfo beginInfo = { VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO };
		beginInfo.renderPass = VkRenderPass(desc.renderPass->Pass());
		beginInfo.framebuffer = VkFramebuffer(desc.framebuffer->Framebuffer(desc.frameIndex));
		beginInfo.renderArea = { {}, { desc.renderArea.x , desc.renderArea.y } };
		beginInfo.clearValueCount = static_cast<u32>(clears.size());
		beginInfo.pClearValues = clears.data();

		vkCmdBeginRenderPass(m_buffer, &beginInfo, VkCommandUtils::GetVkContent(desc.content));
	}

	void GfxVkCommandBuffer::EndRenderPass() const
	{
		vkCmdEndRenderPass(m_buffer);
	}

	void GfxVkCommandBuffer::BindVertices(const Vector<GfxBuffer*> buffers) const
	{
		Vector<VkBuffer> bf(buffers.size());

		usize offset = 0;
		for (u32 i = 0; i < buffers.size(); i++)
			bf[i] = VkBuffer(buffers[i]->Buffer());

		vkCmdBindVertexBuffers(m_buffer, 0, bf.size(), bf.data(), &offset);
	}

	void GfxVkCommandBuffer::BindIndex(const GfxBuffer* buffer, usize offset) const
	{
		vkCmdBindIndexBuffer(m_buffer, VkBuffer(buffer->Buffer()), offset, VK_INDEX_TYPE_UINT32);
	}

	void GfxVkCommandBuffer::DrawVertexed(u32 vertexCount, u32 firstVertex, u32 firstInstance, u32 instanceCount) const
	{
		vkCmdDraw(m_buffer, vertexCount, instanceCount, firstVertex, firstInstance);
	}

	void GfxVkCommandBuffer::DrawIndexed(u32 indexCount, u32 indexOffset, u32 vertexOffset, u32 instanceOffset, u32 instanceCount) const
	{
		vkCmdDrawIndexed(m_buffer, indexCount, instanceCount, 0, vertexOffset, 0);
	}

	void GfxVkCommandBuffer::ExecuteCommands(const Vector<GfxCommandBuffer*> buffers) const
	{
		if (buffers.size() <= 0)
			return;

		Vector<VkCommandBuffer> cmds(buffers.size());
		for (u32 i = 0; i < cmds.size(); i++)
			cmds[i] = VkCommandBuffer(buffers[i]->Buffer());

		if (cmds.size() > 0)
			vkCmdExecuteCommands(m_buffer, cmds.size(), cmds.data());
	}

	void GfxVkCommandBuffer::CopyStageToBuffer(const CopyBufferDesc& desc) const
	{
		VkBufferCopy copyInfo = {};
		copyInfo.srcOffset = desc.srcOffset;
		copyInfo.dstOffset = desc.dstOffset;
		copyInfo.size = desc.size;
		vkCmdCopyBuffer(m_buffer, VkBuffer(desc.src->Buffer()), VkBuffer(desc.dst->Buffer()), 1, &copyInfo);
	}
}
