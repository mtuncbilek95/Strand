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
		TransformComponentRegister() { 
			GlobalComponentResolver::RegisterComponent("TransformComponent", CreateTransformComponent);

			entt::meta<TransformComponent>()
				.type(TransformComponent::StaticTypeId())
				.data<&TransformComponent::position>("position"_hs)
				.data<&TransformComponent::rotation>("rotation"_hs)
				.data<&TransformComponent::scale>("scale"_hs);
		}
	};

	static TransformComponentRegister gbTransformComponentRegistration;
}
