#include "GfxVkPipeline.h"

#include <Runtime/Graphics/Vulkan/Debug/VDebug.h>
#include <Runtime/Graphics/Vulkan/Device/GfxVkDevice.h>
#include <Runtime/Graphics/Vulkan/Descriptor/GfxVkDescriptorLayout.h>
#include <Runtime/Graphics/Vulkan/RenderPass/GfxVkRenderPass.h>
#include <Runtime/Graphics/Vulkan/Shader/GfxVkShader.h>
#include <Runtime/Graphics/Vulkan/Util/VkPipelineUtils.h>
#include <Runtime/Graphics/Vulkan/Util/VkImageUtils.h>

namespace Strand
{
	GfxVkPipeline::GfxVkPipeline(const GfxGraphicsPipelineDesc& desc, GfxDevice* pDevice) : GfxPipeline(desc, pDevice)
	{
		Vector<VkDescriptorSetLayout> dLayouts(desc.layouts.size());
		for (u32 i = 0; i < dLayouts.size(); i++)
			dLayouts[i] = VkDescriptorSetLayout(desc.layouts[i]->DescLayout());

		Vector<VkPushConstantRange> ranges;

		for (u32 i = 0; i < desc.pushes.ranges.size(); i++)
		{
			VkPushConstantRange range = {};
			range.stageFlags = VkPipelineUtils::GetShaderType(desc.pushes.ranges[i].stage);
			range.offset = desc.pushes.ranges[i].offset;
			range.size = desc.pushes.ranges[i].sizeOfData;
		}

		VkPipelineLayoutCreateInfo layoutInfo = { VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO };
		layoutInfo.setLayoutCount = static_cast<u32>(dLayouts.size());
		layoutInfo.pSetLayouts = dLayouts.data();
		layoutInfo.pushConstantRangeCount = static_cast<u32>(ranges.size());
		layoutInfo.pPushConstantRanges = ranges.data();

		VDebug::VkAssert(vkCreatePipelineLayout(VkDevice(Root()->Device()), &layoutInfo, nullptr, &m_layout), "GfxVkPipeline::Graphics");

		Vector<VkPipelineShaderStageCreateInfo> sStages;

		for (u32 i = 0; i < desc.shaders.size(); i++)
		{
			auto& shader = desc.shaders[i];
			VkPipelineShaderStageCreateInfo info = { VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO };
			info.module = VkShaderModule(shader->Shader());
			info.pName = "main";
			info.stage = VkPipelineUtils::GetShaderTypeBit(shader->Type());
			sStages.push_back(info);
		}

		Vector<VkVertexInputBindingDescription> bindings;
		Vector<VkVertexInputAttributeDescription> attributes;
		for (u8 bindIndex = 0; bindIndex < desc.input.bindings.size(); bindIndex++)
		{
			const auto& element = desc.input.bindings[bindIndex];
			VkVertexInputBindingDescription binding = {};
			binding.binding = bindIndex;
			binding.inputRate = element.inputRate == VertexInputRate::Vertex ? VK_VERTEX_INPUT_RATE_VERTEX : VK_VERTEX_INPUT_RATE_INSTANCE;

			u32 offset = 0;
			for (u8 attIndex = 0; attIndex < element.attributes.size(); attIndex++)
			{
				VkVertexInputAttributeDescription attr = {};
				attr.binding = bindIndex;
				attr.location = attIndex;
				attr.format = VkImageUtils::GetVkImgFormat(element.attributes[attIndex]);
				attr.offset = offset;
				attributes.push_back(attr);

				offset += VkImageUtils::GetVkImgSize(element.attributes[attIndex]);
			}
			binding.stride = offset;
			bindings.push_back(binding);
		}

		// VertexInputState
		VkPipelineVertexInputStateCreateInfo vertexInputInfo = { VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO };
		vertexInputInfo.vertexBindingDescriptionCount = static_cast<u32>(bindings.size());
		vertexInputInfo.pVertexBindingDescriptions = bindings.data();
		vertexInputInfo.vertexAttributeDescriptionCount = static_cast<u32>(attributes.size());
		vertexInputInfo.pVertexAttributeDescriptions = attributes.data();

		// InputAssemblyState
		VkPipelineInputAssemblyStateCreateInfo inputAssembly = { VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO };
		inputAssembly.topology = VkPipelineUtils::GetVkTopo(desc.input.topology);
		inputAssembly.primitiveRestartEnable = false;

		Vector<VkDynamicState> dStates;
		for(usize i = 0; i < desc.dynamicStates.size(); i++)
			dStates.push_back(VkPipelineUtils::GetVkDynamicState(desc.dynamicStates[i]));

		// DynamicPipelineState
		VkPipelineDynamicStateCreateInfo dynamicState = { VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO };
		dynamicState.dynamicStateCount = static_cast<u32>(dStates.size());
		dynamicState.pDynamicStates = dStates.data();

		VkViewport vp = {};
		VkRect2D sc = {};

		// ViewportState
		VkPipelineViewportStateCreateInfo viewportState = { VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO };
		viewportState.viewportCount = 1;
		viewportState.pViewports = &vp;
		viewportState.scissorCount = 1;
		viewportState.pScissors = &sc;

		// RasterizationState
		VkPipelineRasterizationStateCreateInfo rasterizer = { VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO };
		rasterizer.depthClampEnable = VK_FALSE;
		rasterizer.rasterizerDiscardEnable = VK_FALSE;
		rasterizer.polygonMode = VkPipelineUtils::GetVkPolygonMode(desc.rasterizer.polygon);
		rasterizer.lineWidth = 1.0f;
		rasterizer.cullMode = VkPipelineUtils::GetVkCullMode(desc.rasterizer.cull);
		rasterizer.frontFace = VkPipelineUtils::GetVkFrontFace(desc.rasterizer.face);
		rasterizer.depthBiasEnable = desc.rasterizer.depthBiasEnable;
		rasterizer.depthBiasConstantFactor = desc.rasterizer.depthBiasConstantFactor;
		rasterizer.depthBiasClamp = desc.rasterizer.depthBiasClamp;
		rasterizer.depthBiasSlopeFactor = desc.rasterizer.depthBiasSlope;

		// MultisampleState
		VkPipelineMultisampleStateCreateInfo multisampling = { VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO };
		multisampling.sampleShadingEnable = VK_FALSE;
		multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

		// ColorBlendAttachmentState
		Vector<VkPipelineColorBlendAttachmentState> colorBlendAttachments;
		for (auto& attachment : desc.blend.attachments)
		{
			VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
			colorBlendAttachment.colorWriteMask = VkPipelineUtils::GetVkColorComponents(attachment.colorMask);

			colorBlendAttachment.blendEnable = attachment.blendEnable;

			colorBlendAttachment.srcColorBlendFactor = VkPipelineUtils::GetVkBlendFactor(attachment.srcColor);
			colorBlendAttachment.dstColorBlendFactor = VkPipelineUtils::GetVkBlendFactor(attachment.dstColor);
			colorBlendAttachment.colorBlendOp = VkPipelineUtils::GetVkBlendOp(attachment.colorOp);

			colorBlendAttachment.srcAlphaBlendFactor = VkPipelineUtils::GetVkBlendFactor(attachment.srcAlpha);
			colorBlendAttachment.dstAlphaBlendFactor = VkPipelineUtils::GetVkBlendFactor(attachment.dstAlpha);
			colorBlendAttachment.alphaBlendOp = VkPipelineUtils::GetVkBlendOp(attachment.alphaOp);

			colorBlendAttachments.push_back(colorBlendAttachment);
		}

		// ColorBlendState
		VkPipelineColorBlendStateCreateInfo colorBlending = { VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO };
		colorBlending.logicOpEnable = desc.blend.logicEnable;
		colorBlending.logicOp = VkPipelineUtils::GetVkLogicOp(desc.blend.logicOp);
		colorBlending.attachmentCount = static_cast<u32>(colorBlendAttachments.size());
		colorBlending.pAttachments = colorBlendAttachments.data();
		colorBlending.blendConstants[0] = 0.0f;
		colorBlending.blendConstants[1] = 0.0f;
		colorBlending.blendConstants[2] = 0.0f;
		colorBlending.blendConstants[3] = 0.0f;

		// DepthStencilState
		VkPipelineDepthStencilStateCreateInfo depthstencil = { VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO };
		depthstencil.depthWriteEnable = desc.depthStencil.depthWriteEnable;
		depthstencil.depthTestEnable = desc.depthStencil.depthTestEnable;
		depthstencil.depthCompareOp = VkPipelineUtils::GetVkCompareOp(desc.depthStencil.depthOp);
		depthstencil.depthBoundsTestEnable = VK_FALSE;
		depthstencil.stencilTestEnable = VK_FALSE;
		depthstencil.minDepthBounds = 0.0f;
		depthstencil.maxDepthBounds = 1.0f;
		depthstencil.front = {};
		depthstencil.back = {};

		VkGraphicsPipelineCreateInfo pipelineInfo{ VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO };
		pipelineInfo.stageCount = static_cast<u32>(sStages.size());
		pipelineInfo.pStages = sStages.data();
		pipelineInfo.pVertexInputState = &vertexInputInfo;
		pipelineInfo.pInputAssemblyState = &inputAssembly;
		pipelineInfo.pViewportState = &viewportState;
		pipelineInfo.pRasterizationState = &rasterizer;
		pipelineInfo.pMultisampleState = &multisampling;
		pipelineInfo.pDepthStencilState = &depthstencil;
		pipelineInfo.pColorBlendState = &colorBlending;
		pipelineInfo.pDynamicState = dStates.size() > 0 ? &dynamicState : nullptr;
		pipelineInfo.layout = m_layout;
		pipelineInfo.renderPass = VkRenderPass(desc.pass->Pass());
		pipelineInfo.subpass = 0;
		pipelineInfo.flags = VkPipelineUtils::GetVkPipelineFlags(desc.flags);
		pipelineInfo.pNext = nullptr;

		VDebug::VkAssert(vkCreateGraphicsPipelines(VkDevice(Root()->Device()), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &m_pipeline), "GfxVkPipeline::Graphics");
	}

	GfxVkPipeline::GfxVkPipeline(const GfxComputePipelineDesc& desc, GfxDevice* pDevice) : GfxPipeline(desc, pDevice)
	{
	}

	GfxVkPipeline::~GfxVkPipeline()
	{
		if (m_pipeline != VK_NULL_HANDLE)
		{
			vkDestroyPipeline(VkDevice(Root()->Device()), m_pipeline, nullptr);
			m_pipeline = VK_NULL_HANDLE;
		}

		if (m_layout != VK_NULL_HANDLE)
		{
			vkDestroyPipelineLayout(VkDevice(Root()->Device()), m_layout, nullptr);
			m_layout = VK_NULL_HANDLE;
		}
	}

	void* GfxVkPipeline::Pipeline() const { return static_cast<void*>(m_pipeline); }
	void* GfxVkPipeline::PipelineLayout() const { return static_cast<void*>(m_layout); }
	void* GfxVkPipeline::PipelineCache() const { return static_cast<void*>(m_cache); }
}