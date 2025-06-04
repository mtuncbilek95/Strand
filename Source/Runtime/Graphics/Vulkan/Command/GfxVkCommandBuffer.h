/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Command/GfxCommandBuffer.h>

#include <vulkan/vulkan.h>

namespace Flax
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
