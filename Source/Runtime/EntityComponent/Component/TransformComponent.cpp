#include "TransformComponent.h"

#include <Runtime/EntityComponent/Scene.h>

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