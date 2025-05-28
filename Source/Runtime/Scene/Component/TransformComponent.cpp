#include "TransformComponent.h"

#include <Runtime/Scene/Scene.h>

namespace Flax
{
	Owned<IComponentBase> CreateTransformComponent()
	{
		return NewOwn<TransformComponent>();
	}

	struct TransformComponentRegister
	{
		TransformComponentRegister() { GlobalComponentResolver::RegisterComponent("TransformComponent", CreateTransformComponent); }
	};

	static TransformComponentRegister gbTransformComponentRegistration;
}
