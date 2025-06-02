#include "ShaderResource.h"

namespace Flax
{
	ShaderResource::ShaderResource(const ShaderResourceProps& desc)
	{
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
