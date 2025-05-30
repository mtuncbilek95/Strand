#include "ProceduralSkyPipeline.h"

#include <Runtime/Graphics/Context/FvkContext.h>
#include <Runtime/Graphics/RenderPass/SkyPass.h>
#include <Runtime/ShaderCompiler/ShaderCompiler.h>

#include <Volk/volk.h>

namespace Flax
{
	ProceduralSkyPipeline::ProceduralSkyPipeline(const ProceduralSkyCreateInfo& createInfo)
	{
		FvkContext& context = FvkContext::Get();

		ReadArray<u32> vByte = ShaderCompiler::CompileShader(createInfo.vPath, "", "main");
		ReadArray<u32> fByte = ShaderCompiler::CompileShader(createInfo.fPath, "", "main");

		// =============== Generate vertex shader =============== //
		VkShaderModuleCreateInfo vertexShaderCreateInfo = { VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO };
		vertexShaderCreateInfo.codeSize = vByte.SizeInBytes();
		vertexShaderCreateInfo.pCode = vByte.Data();
		FvkDebug::Assert(vkCreateShaderModule(context.Device(), &vertexShaderCreateInfo, nullptr, &m_vertexModule), "ProceduralSkyPipeline::VertexShader");

		// =============== Generate fragment shader =============== //
		VkShaderModuleCreateInfo fragmentShaderCreateInfo = { VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO };
		fragmentShaderCreateInfo.codeSize = fByte.SizeInBytes();
		fragmentShaderCreateInfo.pCode = fByte.Data();
		FvkDebug::Assert(vkCreateShaderModule(context.Device(), &fragmentShaderCreateInfo, nullptr, &m_fragmentModule), "ProceduralSkyPipeline::FragmentShader");

		// =============== Create descriptor bindings =============== //
		VkShaderStageFlags descFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
		VkDescriptorSetLayoutBinding uboBinding = {};
		uboBinding.binding = 0;
		uboBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		uboBinding.descriptorCount = 1;
		uboBinding.stageFlags = descFlags;

		// =============== Generate descriptor set layout =============== //
		VkDescriptorSetLayoutCreateInfo dslCreateInfo = { VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO };
		dslCreateInfo.bindingCount = 1;
		dslCreateInfo.pBindings = &uboBinding;
		FvkDebug::Assert(vkCreateDescriptorSetLayout(context.Device(), &dslCreateInfo, nullptr, &m_descriptorLayout), "ProceduralSkyPipeline::DescLayout");

		// =============== Generate pipeline layout =============== //
		VkPipelineLayoutCreateInfo pipelineLayoutInfo = { VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO };
		pipelineLayoutInfo.setLayoutCount = 1;
		pipelineLayoutInfo.pSetLayouts = &m_descriptorLayout;
		FvkDebug::Assert(vkCreatePipelineLayout(context.Device(), &pipelineLayoutInfo, nullptr, &m_layout), "ProceduralSkyPipeline::PipelineLayout");

		VkPipelineShaderStageCreateInfo vertShaderStageInfo = { VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO };
		vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
		vertShaderStageInfo.module = m_vertexModule;
		vertShaderStageInfo.pName = "main";

		VkPipelineShaderStageCreateInfo fragShaderStageInfo = { VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO };
		fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
		fragShaderStageInfo.module = m_fragmentModule;
		fragShaderStageInfo.pName = "main";

		Array<VkPipelineShaderStageCreateInfo, 2> shaderStages = { vertShaderStageInfo, fragShaderStageInfo };

		VkPipelineVertexInputStateCreateInfo vertexInputInfo = { VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO };
		VkPipelineInputAssemblyStateCreateInfo inputAssembly = { VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO };
		inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
		inputAssembly.primitiveRestartEnable = VK_FALSE;

		// =============== Create rasterization state =============== //
		VkPipelineRasterizationStateCreateInfo rasterizer = { VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO };
		rasterizer.depthClampEnable = VK_FALSE;
		rasterizer.rasterizerDiscardEnable = VK_FALSE;
		rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
		rasterizer.cullMode = VK_CULL_MODE_FRONT_BIT;
		rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
		rasterizer.depthBiasEnable = VK_FALSE;
		rasterizer.lineWidth = 1.0f;

		// =============== Create depth stencil state =============== //
		VkPipelineDepthStencilStateCreateInfo depthStencil = { VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO };
		depthStencil.depthTestEnable = VK_FALSE;
		depthStencil.depthWriteEnable = VK_FALSE;
		depthStencil.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
		depthStencil.depthBoundsTestEnable = VK_FALSE;
		depthStencil.stencilTestEnable = VK_FALSE;

		// =============== Create dynamic state =============== //
		Array<VkDynamicState, 2> dynamicStates = { VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR };
		VkPipelineDynamicStateCreateInfo dynamicStateCreateInfo = { VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO };
		dynamicStateCreateInfo.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
		dynamicStateCreateInfo.pDynamicStates = dynamicStates.data();

		VkPipelineViewportStateCreateInfo viewportState = { VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO };
		viewportState.viewportCount = 1;
		viewportState.scissorCount = 1;

		VkColorComponentFlags colorMask =
			VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
			VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

		// =============== Create color blend state =============== //
		VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
		colorBlendAttachment.colorWriteMask = colorMask;
		colorBlendAttachment.blendEnable = VK_FALSE;

		VkPipelineColorBlendStateCreateInfo colorBlending = { VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO };
		colorBlending.logicOpEnable = VK_FALSE;
		colorBlending.attachmentCount = 1;
		colorBlending.pAttachments = &colorBlendAttachment;

		// =============== Create multisample state =============== //
		VkPipelineMultisampleStateCreateInfo multisampleState = { VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO };
		multisampleState.sampleShadingEnable = VK_FALSE;
		multisampleState.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
		multisampleState.minSampleShading = 1.0f;
		multisampleState.pSampleMask = nullptr;
		multisampleState.alphaToCoverageEnable = VK_FALSE;
		multisampleState.alphaToOneEnable = VK_FALSE;

		// =============== Generate pipeline =============== //
		VkGraphicsPipelineCreateInfo pipelineInfo = { VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO };
		pipelineInfo.stageCount = 2;
		pipelineInfo.pStages = shaderStages.data();
		pipelineInfo.pVertexInputState = &vertexInputInfo;
		pipelineInfo.pInputAssemblyState = &inputAssembly;
		pipelineInfo.pViewportState = &viewportState;
		pipelineInfo.pRasterizationState = &rasterizer;
		pipelineInfo.pDepthStencilState = &depthStencil;
		pipelineInfo.pColorBlendState = &colorBlending;
		pipelineInfo.pDynamicState = &dynamicStateCreateInfo;
		pipelineInfo.pMultisampleState = &multisampleState;
		pipelineInfo.layout = m_layout;
		pipelineInfo.renderPass = createInfo.pass->Pass();
		pipelineInfo.subpass = 0;
		FvkDebug::Assert(vkCreateGraphicsPipelines(context.Device(), nullptr, 1, &pipelineInfo, nullptr, &m_pipeline), "ProceduralSkyPipeline::Pipeline");
	}

	ProceduralSkyPipeline::~ProceduralSkyPipeline()
	{
	}
}

