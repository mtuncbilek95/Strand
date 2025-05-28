#include "Mesh.h"

#include <Runtime/Vulkan/Context/VContext.h>

#include <Runtime/Services/ResourceService.h>

#include <Runtime/Resource/Shader/ShaderResource.h>
#include <Runtime/Resource/PipelineState/PipelineState.h>
#include <Runtime/Resource/Importer/MeshImporter.h>

namespace Flax
{
	Mesh::Mesh(const String& meshFolder)
	{
		String fullPath = meshFolder + "Mesh.gltf";
		m_cpuData = MeshImporter::ReadGeometry(fullPath);

		ShaderResourceProps vertProp =
		{
			.stageType = VK_SHADER_STAGE_VERTEX_BIT,
			.path = R"(D:\Projects\Flax\Shaders\BasicPBR.vert)",
		};
		m_vertResource = ServiceLocator::Get<ResourceService>()->RegisterResource<ShaderResource>(vertProp);

		ShaderResourceProps fragProp =
		{
			.stageType = VK_SHADER_STAGE_FRAGMENT_BIT,
			.path = R"(D:\Projects\Flax\Shaders\BasicPBR.frag)",
		};
		m_fragResource = ServiceLocator::Get<ResourceService>()->RegisterResource<ShaderResource>(fragProp);

		DescLayoutProps layoutProp =
		{
			.bindings =
			{
				{ 0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1, VK_SHADER_STAGE_VERTEX_BIT },
				{ 1, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1, VK_SHADER_STAGE_VERTEX_BIT }
			},
			.createFlags = 0
		};

		PipelineStateProps psoProp =
		{
			.shaders = { 
				{PipelineStage::Vertex, m_vertResource}, 
				{PipelineStage::Fragment, m_fragResource}
			},
			.renderTarget = nullptr,
			.layoutProps = layoutProp
		};
		m_pipelineResource = ServiceLocator::Get<ResourceService>()->RegisterResource<PipelineState>(psoProp);

		/*GraphicsPipelineProps gPipelineProp =
		{
			.layouts = { m_descLayout.get() },
			.shaderStages = { m_vertResource->GetShader(), m_fragResource->GetShader() },
			.inputAssembler = {VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, false, {{VK_VERTEX_INPUT_RATE_VERTEX, {VK_FORMAT_R32G32B32_SFLOAT, VK_FORMAT_R32G32B32_SFLOAT,
			VK_FORMAT_R32G32B32_SFLOAT, VK_FORMAT_R32G32B32_SFLOAT, VK_FORMAT_R32G32B32A32_SFLOAT, VK_FORMAT_R32G32_SFLOAT }}}},
			.viewportState = {true, {0.f, 0.f, 0.f, 0.f, 0.f, 1.f}, true, {{ 0, 0 }, { 0, 0 }}},
			.rasterizerState = {true, 0.f, 1.f, 0.f, VK_POLYGON_MODE_FILL, VK_CULL_MODE_BACK_BIT, VK_FRONT_FACE_CLOCKWISE},
			.blendState = {true, VK_LOGIC_OP_COPY, {{false, VK_BLEND_FACTOR_ZERO, VK_BLEND_FACTOR_ONE, VK_BLEND_OP_ADD,
			VK_BLEND_FACTOR_ZERO, VK_BLEND_FACTOR_ONE, VK_BLEND_OP_ADD, VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT}}},
			.depthStencilState = {true, true, VK_COMPARE_OP_LESS, false, false, {}, {}, 0.f, 1.f},
			.renderPass = nullptr
		};*/
	}
}
