/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Command/GfxCommandBuffer.h>

#include <vulkan/vulkan.h>

namespace Strand
{
	class GfxVkCommandBuffer final : public GfxCommandBuffer
	{
	public:
		GfxVkCommandBuffer(const GfxCommandBufferDesc& desc, GfxDevice* pDevice);
		~GfxVkCommandBuffer() override final;

		void* Buffer() const override final;

		void BeginRecord(CommandBufferUsage usage = CommandBufferUsage::OneTimeSubmit) const override final;
		void BeginRecord(const InheritanceDesc& desc, CommandBufferUsage usage = CommandBufferUsage::OneTimeSubmit) const override final;
		void EndRecord() const override final;

		void BeginRenderPass(const BeginRenderDesc& desc) const override final;
		void EndRenderPass() const override final;

		void BindVertices(const Vector<GfxBuffer*> buffers) const override final;
		void BindIndex(const GfxBuffer* buffer, usize offset) const override final;

		void DrawVertexed(u32 vertexCount, u32 firstVertex, u32 firstInstance, u32 instanceCount) const override final;
		void DrawIndexed(u32 indexCount, u32 indexOffset, u32 vertexOffset, u32 instanceOffset, u32 instanceCount) const override final;
		void ExecuteCommands(const Vector<GfxCommandBuffer*> buffers) const override final;

		void CopyStageToBuffer(const CopyBufferDesc& desc) const override final;

	private:
		VkCommandBuffer m_buffer;
	};
}
