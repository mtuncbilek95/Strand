#include "RenderComponent.h"

#include <Runtime/Scene/Scene.h>

namespace Flax
{
	Owned<IComponentBase> CreateRenderComponent()
	{
		return NewOwn<RenderComponent>();
	}

	struct RenderComponentRegister
	{
		RenderComponentRegister() { GlobalComponentResolver::RegisterComponent("RenderComponent", CreateRenderComponent); }
	};

	static RenderComponentRegister gbRenderComponentRegistration;
}
