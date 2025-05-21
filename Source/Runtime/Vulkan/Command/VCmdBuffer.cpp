#include "VCmdBuffer.h"

#include <Runtime/Vulkan/Debug/VDebug.h>
#include <Runtime/Vulkan/Device/VDevice.h>
#include <Runtime/Vulkan/Command/VCmdPool.h>
#include <Runtime/Vulkan/RenderPass/VRenderPass.h>
#include <Runtime/Vulkan/Framebuffer/VFramebuffer.h>
#include <Runtime/Vulkan/Buffer/VBuffer.h>
#include <Runtime/Vulkan/Image/VImage.h>
#include <Runtime/Vulkan/Image/VImageView.h>
#include <Runtime/Vulkan/Pipeline/VPipeline.h>
#include <Runtime/Vulkan/Descriptor/VDescriptorSet.h>

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

	void VCmdBuffer::BeginRecord(const InheritanceProps& desc, VkCommandBufferUsageFlags flags) const
	{
		vkResetCommandBuffer(m_buffer, VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT);

		VkCommandBufferBeginInfo info = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO };
		info.flags = flags;

		VkCommandBufferInheritanceInfo inheritInfo = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO };
		if (flags & VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT || flags & VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT)
		{
			inheritInfo.renderPass = desc.renderPass->GetVkRenderPass();
			inheritInfo.framebuffer = desc.framebuffer ? desc.framebuffer->GetVkFramebuffer() : VK_NULL_HANDLE;
			inheritInfo.subpass = desc.subpass;
			inheritInfo.occlusionQueryEnable = false;

			info.pInheritanceInfo = &inheritInfo;
		}

		VDebug::VkAssert(vkBeginCommandBuffer(m_buffer, &info), "VCmdBUffer");

		m_status = CommandStatus::Recording;
	}

	void VCmdBuffer::EndRecord() const
	{
		vkEndCommandBuffer(m_buffer);

		m_status = CommandStatus::ReadyToExecute;
	}

	void VCmdBuffer::BeginRenderPass(const RenderPassBeginParams& params)
	{
		VkRenderPassBeginInfo beginInfo = { VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO };
		beginInfo.renderPass = params.renderPass->GetVkRenderPass();
		beginInfo.framebuffer = params.framebuffer->GetVkFramebuffer(params.frameIndex);
		beginInfo.renderArea = { {}, { params.renderArea.x , params.renderArea.y } };
		beginInfo.clearValueCount = static_cast<u32>(params.clearValues.size());
		beginInfo.pClearValues = params.clearValues.data();

		vkCmdBeginRenderPass(m_buffer, &beginInfo, params.contents);

		m_boundRenderPass = params.renderPass;
		m_boundFramebuffer = params.framebuffer;
	}

	void VCmdBuffer::EndRenderPass()
	{
		vkCmdEndRenderPass(m_buffer);

		m_boundRenderPass = nullptr;
		m_boundFramebuffer = nullptr;
	}

	void VCmdBuffer::BindPipeline(VPipeline* pPipeline)
	{
		vkCmdBindPipeline(m_buffer, pPipeline->GetVkBindPoint(), pPipeline->GetVkPipeline());

		m_boundPipeline = pPipeline;
	}

	void VCmdBuffer::BindDescriptors(const Vector<VDescSet*>& sets) const
	{
		Vector<VkDescriptorSet> descs(sets.size());

		for (u32 i = 0; i < descs.size(); i++)
			descs[i] = sets[i]->GetVkSet();

		u32 offset = 0;
		vkCmdBindDescriptorSets(m_buffer, m_boundPipeline->GetVkBindPoint(), m_boundPipeline->GetVkLayout(), 0, descs.size(), descs.data(), 0, &offset);
	}

	void VCmdBuffer::BindVertexBuffers(const Vector<VBuffer*>& buffers) const
	{
		Vector<VkBuffer> bf(buffers.size());
		usize offset = 0;
		for (u32 i = 0; i < buffers.size(); i++)
			bf[i] = buffers[i]->GetVkBuffer();

		vkCmdBindVertexBuffers(m_buffer, 0, bf.size(), bf.data(), &offset);
	}

	void VCmdBuffer::BindIndexBuffer(VBuffer* iBuffer, usize offset) const
	{
		vkCmdBindIndexBuffer(m_buffer, iBuffer->GetVkBuffer(), offset, VK_INDEX_TYPE_UINT32);
	}

	void VCmdBuffer::DrawCommon(u32 vertexCount, u32 firstVertex, u32 firstInstance, u32 instanceCount) const
	{
		vkCmdDraw(m_buffer, vertexCount, instanceCount, firstVertex, firstInstance);
	}

	void VCmdBuffer::DrawIndexed(u32 indexCount, u32 indexOffset, u32 vertexOffset, u32 instanceOffset, u32 instanceCount) const
	{
		vkCmdDrawIndexed(m_buffer, indexCount, instanceCount, 0, vertexOffset, 0);
	}

	void VCmdBuffer::ExecuteCommands(const Vector<VCmdBuffer*>& buffers) const
	{
		if (buffers.size() <= 0)
			return;

		Vector<VkCommandBuffer> cmds;
		for (u32 i = 0; i < buffers.size(); i++)
		{
			if (buffers[i]->m_status == CommandStatus::ReadyToExecute)
				cmds.push_back(buffers[i]->GetVkCmdBuffer());
			else
				continue;
		}

		if(cmds.size() > 0)
			vkCmdExecuteCommands(m_buffer, cmds.size(), cmds.data());

		for (u32 i = 0; i < cmds.size(); i++)
			buffers[i]->m_status = CommandStatus::Idle;
	}

	void VCmdBuffer::CopyStageToBuffer(const CopyBufferProps& params) const
	{
		VkBufferCopy copyInfo = {};
		copyInfo.srcOffset = params.srcOffset;
		copyInfo.dstOffset = params.dstOffset;
		copyInfo.size = params.size;
		vkCmdCopyBuffer(m_buffer, params.srcBuffer->GetVkBuffer(), params.dstBuffer->GetVkBuffer(), 1, &copyInfo);
	}

	void VCmdBuffer::CopyStageToImage(const CopyImageProps& params) const
	{
		VkBufferImageCopy copyInfo = {};

		vkCmdCopyBufferToImage(m_buffer, params.srcBuffer->GetVkBuffer(), params.dstImage->GetVkImage(), VK_IMAGE_LAYOUT_UNDEFINED, 1, &copyInfo);
	}
}