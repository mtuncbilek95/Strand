#include "ShaderResource.h"

#include <Runtime/Renderer/Renderer.h>

namespace Flax
{
	ShaderResource::ShaderResource(const ShaderResourceProps& desc) : m_props(desc)
	{
		ShaderProps shaderProp =
		{
			.shaderPath = desc.path,
			.includePath = "",
			.entryPoint = "main",
			.shaderStage = desc.stageType
		};
		m_shader = NewRef<VShader>(shaderProp, ServiceLocator::Get<Renderer>()->GetDevice());
	}

	ShaderResource::~ShaderResource()
	{
		m_shader.reset();
	}

	void ShaderResource::Compile()
	{
	}
}
