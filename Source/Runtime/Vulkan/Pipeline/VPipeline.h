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
	class VDescLayout;
	class VShader;
	class VRenderPass;

	struct InputBinding final
	{
		VkVertexInputRate inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
		Vector<VkFormat> attributes;
	};

	struct InputAssembler final
	{
		VkPrimitiveTopology topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		b8 primitiveRestartEnable = false;
		Vector<InputBinding> bindings;
	};

	struct ViewportState final
	{
		b8 dynamicView = false;
		VkViewport viewport;
		b8 dynamicScissor = false;
		VkRect2D scissor;
	};

	struct RasterizerState final
	{
		b8 depthBiasEnable = false;
		f32 depthBiasConstantFactor = 0.0f;
		f32 depthBiasClamp = 1.0f;
		f32 depthBiasSlopeFactor = 0.0f;
		VkPolygonMode polygonMode = VK_POLYGON_MODE_FILL;
		VkCullModeFlags cullMode = VK_CULL_MODE_FRONT_BIT;
		VkFrontFace frontFace = VK_FRONT_FACE_CLOCKWISE;
	};

	struct BlendStateAttachment final
	{
		b8 blendEnable = false;
		VkBlendFactor srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
		VkBlendFactor dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
		VkBlendOp colorBlendOp = VK_BLEND_OP_ADD;
		VkBlendFactor srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
		VkBlendFactor dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
		VkBlendOp alphaBlendOp = VK_BLEND_OP_ADD;
		VkColorComponentFlags colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	};

	struct BlendState final
	{
		b8 logicOpEnable = false;
		VkLogicOp logicOp = VK_LOGIC_OP_COPY;
		Vector<BlendStateAttachment> attachments;
	};

	struct DepthStencilState final
	{
		b8 depthTestEnable = false;
		b8 depthWriteEnable = false;
		VkCompareOp depthCompareOp = VK_COMPARE_OP_ALWAYS;
		b8 depthBoundsTestEnable = false;
		b8 stencilTestEnable = false;
		VkStencilOpState front = {};
		VkStencilOpState back = {};
		f32 minDepthBounds = 0.0f;
		f32 maxDepthBounds = 1.0f;
	};

	struct PushRange final
	{
		VkShaderStageFlags flags;
		u32 offset = 0;
		u32 sizeOfCurrentPush;
	};

	struct PushConstants final
	{
		Vector<PushRange> ranges;
	};

	struct GraphicsPipelineProps final
	{
		Vector<VDescLayout*> layouts;
		Vector<VShader*> shaderStages;
		InputAssembler inputAssembler;
		ViewportState viewportState;
		RasterizerState rasterizerState;
		PushConstants pushConstants;
		BlendState blendState;
		DepthStencilState depthStencilState;
		VRenderPass* renderPass;

		VkPipelineCreateFlags createFlag;
	};

	class VPipeline final : public VObject
	{
	public:
		VPipeline(const GraphicsPipelineProps& desc, VDevice* pDevice);
		~VPipeline() override final;

		inline VkPipeline GetVkPipeline() const { return m_pipeline; }
		inline VkPipelineLayout GetVkLayout() const { return m_layout; }
		inline VkPipelineBindPoint GetVkBindPoint() const { return m_bindPoint; }

	private:
		GraphicsPipelineProps m_props;

		VkPipeline m_pipeline;
		VkPipelineLayout m_layout;
		VkPipelineBindPoint m_bindPoint;
	};
}