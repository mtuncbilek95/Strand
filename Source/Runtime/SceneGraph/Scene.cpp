#include "Scene.h"

#include <Runtime/SceneGraph/Entity.h>

namespace Strand
{
	Scene::Scene(const String& sceneName) : m_name(sceneName)
	{
	}

	Scene::~Scene()
	{
	}

	void Scene::AddChild(const String& name)
	{
		String newName;
		if (name.empty())
			newName = "ChildOf" + m_name;
		else
			newName = name;

		m_entities.push_back(NewRef<Entity>(newName, this));
	}

	void Scene::RemoveChild(i32 childId)
	{
		m_entities.erase(
			std::remove_if(m_entities.begin(), m_entities.end(),
				[childId](const Ref<Entity>& child) {
					return child->GetId() == childId;
				}),
			m_entities.end());
	}

	Entity* Scene::FindChild(const String& childName)
	{
		for (auto& child : m_entities)
		{
			if (child->GetName() == childName)
				return child.get();
		}

		return nullptr;
	}
}