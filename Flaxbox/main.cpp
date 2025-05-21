#include <Runtime/Window/BasicWindow.h>
#include <Runtime/Renderer/Renderer.h>

#include <Runtime/Vulkan/Descriptor/VDescriptorLayout.h>
#include <Runtime/Vulkan/Descriptor/VDescriptorPool.h>
#include <Runtime/Vulkan/Descriptor/VDescriptorSet.h>
#include <Runtime/Vulkan/Shader/VShader.h>
#include <Runtime/Vulkan/Pipeline/VPipeline.h>

#include <Runtime/Vulkan/Command/VCmdPool.h>
#include <Runtime/Vulkan/Command/VCmdBuffer.h>

#include <Runtime/EntityComponent/Manager/SceneManager.h>
#include <Runtime/EntityComponent/Scene.h>
#include <Runtime/EntityComponent/Entity.h>
#include <Runtime/EntityComponent/Component/RenderComponent.h>

#include "MeshObject.h"

using namespace Flax;

int main()
{
	WindowProps w11Props =
	{
		.windowName = "Flax",
		.windowSize = { 1280, 720 },
		.windowMode = WindowMode::Windowed
	};
	Ref<BasicWindow> window = NewRef<BasicWindow>(w11Props);

	RendererProps rendProps =
	{
		.rendererSize = w11Props.windowSize,
		.windowHandle = window->GetHandle()
	};
	Renderer vkRenderer(rendProps);

	Ref<Scene> testScene = NewRef<Scene>();
	SceneManager::Get().SetCurrentScene(testScene.get());

	Ref<Entity> gameObject1 = testScene->AddEntity(nullptr);
	gameObject1->AddComponent<RenderComponent>();

	/*DescLayoutProps vkMeshDescLayoutProps =
	{
		.bindings =
		{
			{ 0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1, VK_SHADER_STAGE_VERTEX_BIT },
			{ 1, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1, VK_SHADER_STAGE_VERTEX_BIT }
		},
		.createFlags = 0
	};
	Ref<VDescLayout> vkMeshDescLayout = NewRef<VDescLayout>(vkMeshDescLayoutProps, vkRenderer.TempDevice());

	DescPoolProps vkDescPoolProps =
	{
		.poolSizes =
		{
			{ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 2 }
		},
		.maxSets = 2
	};
	Ref<VDescPool> vkDescPool = NewRef<VDescPool>(vkDescPoolProps, vkRenderer.TempDevice());
	Ref<VDescSet> vkDescSet = NewRef<VDescSet>(DescSetProps({ vkMeshDescLayout.get(), vkDescPool.get() }), vkRenderer.TempDevice());

	ShaderProps vertProp =
	{
		.shaderPath = R"(D:\Projects\Flax\Flaxbox\TestObj.vert)",
		.includePath = "",
		.entryPoint = "main",
		.shaderStage = VK_SHADER_STAGE_VERTEX_BIT
	};
	Ref<VShader> vkVShader = NewRef<VShader>(vertProp, vkRenderer.TempDevice());

	ShaderProps fragProp =
	{
		.shaderPath = R"(D:\Projects\Flax\Flaxbox\TestObj.frag)",
		.includePath = "",
		.entryPoint = "main",
		.shaderStage = VK_SHADER_STAGE_FRAGMENT_BIT
	};
	Ref<VShader> vkFShader = NewRef<VShader>(fragProp, vkRenderer.TempDevice());

	GraphicsPipelineProps vkMeshGrapProp =
	{
		.layouts = {&*vkMeshDescLayout},
		.shaderStages = {&*vkVShader, &*vkFShader},
		.inputAssembler = {VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, false, {{VK_VERTEX_INPUT_RATE_VERTEX, {VK_FORMAT_R32G32B32_SFLOAT, VK_FORMAT_R32G32B32_SFLOAT,
		VK_FORMAT_R32G32B32_SFLOAT, VK_FORMAT_R32G32B32_SFLOAT, VK_FORMAT_R32G32B32A32_SFLOAT, VK_FORMAT_R32G32_SFLOAT }}}},
		.viewportState = {false, {0.f, 0.f, (f32)window->GetSize()[0], (f32)window->GetSize()[1], 0.f, 1.f},
		false, {{0, 0}, { window->GetSize()[0], window->GetSize()[1]}}},
		.rasterizerState = {true, 0.f, 1.f, 0.f, VK_POLYGON_MODE_FILL, VK_CULL_MODE_BACK_BIT, VK_FRONT_FACE_CLOCKWISE},
		.blendState = {true, VK_LOGIC_OP_COPY, {{false, VK_BLEND_FACTOR_ZERO, VK_BLEND_FACTOR_ONE, VK_BLEND_OP_ADD,
		VK_BLEND_FACTOR_ZERO, VK_BLEND_FACTOR_ONE, VK_BLEND_OP_ADD, VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT}}},
		.depthStencilState = {true, true, VK_COMPARE_OP_LESS, false, false, {}, {}, 0.f, 1.f},
		.renderPass = vkRenderer.TempPass()
	};
	Ref<VPipeline> vkMeshPipeline = NewRef<VPipeline>(vkMeshGrapProp, vkRenderer.TempDevice());

	MeshObject meshObj;
	meshObj.Load(R"(D:\Projects\_ReadOnly\glTF-Sample-Models\2.0\SciFiHelmet\glTF\SciFiHelmet.gltf)", vkRenderer.TempTransfer(), vkRenderer.TempDevice());
	vkDescSet->UpdateData(SetUpdateProps(
		{
			{ {meshObj.GetModelBuffer()}, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1, 0, 0, 0},
			{ {meshObj.GetVPBuffer()}, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1, 0, 0, 1}
		}));*/

	window->Show();
	while (window->IsActive())
	{
		window->ProcessEvents();
		vkRenderer.Run();
	}
	vkRenderer.Stop();

	window->Hide();
}