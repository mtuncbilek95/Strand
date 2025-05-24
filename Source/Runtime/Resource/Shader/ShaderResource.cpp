#include "ShaderResource.h"

#include <Runtime/Renderer/Renderer.h>

namespace Flax
{
	ShaderResource::ShaderResource()
	{
	}

	ShaderResource::~ShaderResource()
	{
		m_shader.reset();
	}

	void ShaderResource::Load(const ShaderResourceProps& desc)
	{
	}

	void ShaderResource::Compile()
	{
	}

	Ref<IResource> CreateShaderResource()
	{
		return NewRef<ShaderResource>();
	}

	struct ShaderResourceRegister
	{
		ShaderResourceRegister() { GlobalResourceResolver::RegisterResource("ShaderResource", CreateShaderResource); }
	};

	static ShaderResourceRegister gbShaderResourceRegistry;
}
