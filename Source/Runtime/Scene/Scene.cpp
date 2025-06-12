#include "Scene.h"

#include <Runtime/Scene/Component.h>
#include <Runtime/Scene/Entity.h>

namespace Flax
{
	Scene::Scene(const String& name) : m_registry(), 
		m_name(name)
	{
		m_rootEntity = NewRef<Entity>(this, nullptr);
	}

	Scene::~Scene()
	{
	}

	Entity* Scene::AddEntity(Entity* parent)
	{
		if (parent)
		{
			auto* child = parent->AddChild();
			return child;
		}

		auto* child = m_rootEntity->AddChild();
		return child;
	}

	void Scene::RemoveEntity(Entity* entity)
	{
		if (entity)
		{
			entity->RemoveAllChildren();
			entity = nullptr;
		}
	}

	Entity* Scene::Child(usize index) const
	{
		return m_rootEntity->Child(index);
	}

	usize Scene::Count() const
	{
		return m_rootEntity->Count();
	}
}