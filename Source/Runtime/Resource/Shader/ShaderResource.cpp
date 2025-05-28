#include "ShaderResource.h"

#include <Runtime/Vulkan/Context/VContext.h>

namespace Flax
{
	ShaderResource::ShaderResource(const ShaderResourceProps& desc)
	{
		if (m_shader)
			return;

		ShaderProps prop =
		{
			.shaderPath = desc.path,
			.shaderStage = desc.stageType
		};
		m_shader = NewRef<VShader>(prop, VContext::Get().Device());
	}

	ShaderResource::~ShaderResource()
	{
	}

	Ref<IResource> CreateShaderResource(const Any& args)
	{
		const auto& props = std::any_cast<const ShaderResourceProps&>(args);
		return NewRef<ShaderResource>(props);
	}

	struct ShaderResourceRegister
	{
		ShaderResourceRegister() { GlobalResourceResolver::RegisterResource("ShaderResource", CreateShaderResource); }
	};

	static ShaderResourceRegister gbShaderResourceRegistry;
}
