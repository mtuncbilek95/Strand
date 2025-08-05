#include "Entity.h"

namespace Strand
{
	i32 Entity::m_nextId = 1;

	Entity::Entity(const String& entityName, Scene* scene, Entity* pParent) : m_id(m_nextId++), 
		m_name(entityName), m_isActive(true), m_parent(pParent), m_ownerScene(scene)
	{
	}

	void Entity::AddChild(const String& name)
	{
		String newName;
		if (name.empty())
			newName = "ChildOf" + m_name;
		else
			newName = name;

		m_children.push_back(NewRef<Entity>(newName, m_ownerScene));
	}

	void Entity::RemoveChild(i32 childId)
	{
		m_children.erase(
			std::remove_if(m_children.begin(), m_children.end(),
				[childId](const Ref<Entity>& child) {
					return child->GetId() == childId;
				}),
			m_children.end());
	}

	Entity* Entity::FindChild(const String& childName)
	{
		for (auto& child : m_children)
		{
			if (child->GetName() == childName)
				return child.get();
		}

		return nullptr;
	}

	Entity* Entity::GetChild(usize index) const
	{
		if (index == u64_max)
			return nullptr;

		return m_children.at(index).get();
	}
}