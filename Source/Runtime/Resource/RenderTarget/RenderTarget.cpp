#include "RenderTarget.h"

namespace Flax
{
	RenderTarget::RenderTarget(const RenderTargetProps& desc)
	{
	}

	RenderTarget::~RenderTarget()
	{
	}

	Ref<IResource> CreateRenderTarget(const Any& args)
	{
		const auto& props = std::any_cast<const RenderTargetProps&>(args);
		return NewRef<RenderTarget>(props);
	}

	struct RenderTargetRegister
	{
		RenderTargetRegister() { GlobalResourceResolver::RegisterResource("RenderTarget", CreateRenderTarget); }
	};

	static RenderTargetRegister gbRenderTargetRegistry;
}