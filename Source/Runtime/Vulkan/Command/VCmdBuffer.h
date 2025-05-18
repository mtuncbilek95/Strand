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
	class VFramebuffer;
	class VBuffer;
	class VImage;
	class VPipeline;
	class VDescSet;

	struct CopyBufferProps final
	{
		VBuffer* srcBuffer = nullptr;
		VBuffer* dstBuffer = nullptr;
		u32 srcOffset = 0;
		u32 dstOffset = 0;
		u32 size = 0;
	};

	struct CopyImageProps final
	{
		VBuffer* srcBuffer = nullptr;
		VImage* dstImage = nullptr;
	};

	struct RenderPassBeginParams final
	{
		VRenderPass* renderPass;
		VFramebuffer* framebuffer;
		u32 frameIndex = 0;
		Math::Vec2u renderArea = {};
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

		void CopyStageToBuffer(const CopyBufferProps& params) const;
		void CopyStageToImage(const CopyImageProps& params) const;

	private:
		CmdBufferProps m_props;

		VkCommandBuffer m_buffer;

		VRenderPass* m_boundRenderPass;
		VFramebuffer* m_boundFramebuffer;
		VPipeline* m_boundPipeline;
	};
}