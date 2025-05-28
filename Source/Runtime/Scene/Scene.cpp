#include "Scene.h"

#include <Runtime/Scene/Component.h>
#include <Runtime/Scene/Entity.h>

namespace Flax
{
	Scene::Scene() : m_registry()
	{
		m_rootEntity = NewRef<Entity>(this, nullptr);
	}

	Scene::~Scene()
	{
	}

	Ref<Entity> Scene::AddEntity(Ref<Entity> parent)
	{
		if (parent)
		{
			auto child = parent->AddChild();
			return child;
		}

		auto child = m_rootEntity->AddChild();
		return child;
	}

	void Scene::RemoveEntity(Ref<Entity> entity)
	{
		if (entity)
		{
			entity->RemoveAllChildren();
			entity = nullptr;
		}
	}
}