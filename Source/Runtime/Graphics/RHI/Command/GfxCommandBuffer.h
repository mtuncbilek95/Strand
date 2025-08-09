/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Object/GfxObject.h>
#include <Runtime/Graphics/RHI/Command/GfxCommandBufferDesc.h>

namespace Strand
{
	class GfxBuffer;

	/**
	 * @class GfxCommandBuffer
	 * @brief All purpose command buffer for RHI. CommandBuffer a.k.a
	 * CommandList is being used for recording the commands of rendering
	 * system such as DrawIndexed, DispatchCompute etc.
	 */
	class GfxCommandBuffer : public GfxObject
	{
	public:
		GfxCommandBuffer(const GfxCommandBufferDesc& desc, GfxDevice* pDevice);
		virtual ~GfxCommandBuffer() override = default;

		virtual void* Buffer() const = 0;
		GfxCommandPool* Pool() const { return m_desc.pool; }

		virtual void BeginRecord(CommandBufferUsage usage = CommandBufferUsage::OneTimeSubmit) const = 0;
		virtual void BeginRecord(const InheritanceDesc& desc, CommandBufferUsage usage = CommandBufferUsage::OneTimeSubmit) const = 0;
		virtual void EndRecord() const = 0;

		virtual void BeginRenderPass(const BeginRenderDesc& desc) const = 0;
		virtual void EndRenderPass() const = 0;

		virtual void BindVertices(const Vector<GfxBuffer*> buffers) const = 0;
		virtual void BindIndex(const GfxBuffer* buffer, usize offset) const = 0;

		virtual void DrawVertexed(u32 vertexCount, u32 firstVertex, u32 firstInstance, u32 instanceCount) const = 0;
		virtual void DrawIndexed(u32 indexCount, u32 indexOffset, u32 vertexOffset, u32 instanceOffset, u32 instanceCount) const = 0;
		virtual void ExecuteCommands(const Vector<GfxCommandBuffer*> buffers) const = 0;

		virtual void CopyStageToBuffer(const CopyBufferDesc& desc) const = 0;

	private:
		GfxCommandBufferDesc m_desc;
	};
}
