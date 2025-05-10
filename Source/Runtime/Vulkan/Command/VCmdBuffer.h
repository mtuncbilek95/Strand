/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Vulkan/Object/VObject.h>

namespace Flax
{
	class VCmdPool;
	class VRenderPass;
	class VPipeline;
	class VDescSet;
	class VBuffer;
    class VFramebuffer;

    struct CopyBufferProps final
    {

    };

    struct RenderPassBeginParams
    {
        VRenderPass* renderPass;
        VFramebuffer* framebuffer;
        u32 frameIndex = 0;
        VkRect2D renderArea = {};
        Vector<VkClearValue> clearValues;
        VkSubpassContents contents = VK_SUBPASS_CONTENTS_INLINE;
    };

	struct CmdBufferProps final
	{
		VkCommandBufferLevel cmdLevel = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		VCmdPool* pool = nullptr;
	};

	class VCmdBuffer final : public VObject
	{
	public:
		VCmdBuffer(const CmdBufferProps& desc, VDevice* pDevice);
		~VCmdBuffer() override final;

		inline VkCommandBuffer GetVkCmdBuffer() const { return m_buffer; }

		void BeginRecord(VkCommandBufferUsageFlags flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT) const;
		void EndRecord() const;

		void BeginRenderPass(const RenderPassBeginParams& params);
		void EndRenderPass();

		void BindPipeline(VPipeline* pPipeline);
		void BindDescriptors(const Vector<VDescSet*>& descriptors) const;
		void BindVertexBuffers(const Vector<VBuffer*>& buffers) const;
		void BindIndexBuffer(VBuffer* buffer, usize offset) const;

		void DrawCommon(u32 vertexCount, u32 firstVertex, u32 firstInstance, u32 instanceCount) const;
		void DrawIndexed(u32 indexCount, u32 indexOffset, u32 vertexOffset, u32 instanceOffset, u32 instanceCount) const;
		void ExecuteCommands(const Vector<VCmdBuffer*>& buffers) const;

        void CopyStageToBuffer(VBuffer* src, VBuffer* dst, const CopyBufferProps& copyProps) const;

	private:
		CmdBufferProps m_props;

		VkCommandBuffer m_buffer;

		VRenderPass* m_boundRenderPass;
        VFramebuffer* m_boundFramebuffer;
		VPipeline* m_boundPipeline;
	};
}