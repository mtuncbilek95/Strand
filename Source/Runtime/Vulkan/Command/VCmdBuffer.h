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

	struct RenderPassBeginParams
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

	private:
		CmdBufferProps m_props;

		VkCommandBuffer m_buffer;

		VRenderPass* m_boundRenderPass;
		VFramebuffer* m_boundFramebuffer;
	};
}