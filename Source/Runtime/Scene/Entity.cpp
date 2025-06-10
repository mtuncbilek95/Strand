#include "Entity.h"

namespace Flax
{
	Entity::Entity(Scene* owner, Entity* parent) : m_owner(owner), m_parent(parent), m_entityId(entt::null)
	{
		if (m_parent)
		{
			m_entityId = owner->Registry().create();
			Log::Debug(LogType::ECS, "Creating child entity with name {}", "Default Entity " + std::to_string(m_parent->Count()));
			m_name += " " + std::to_string(m_parent->Count());
		}
		else
		{
			Log::Debug(LogType::ECS, "Creating root entity");
			m_name = "Root";
		}
	}

	Entity::~Entity()
	{
		if (m_parent)
		{
			m_owner->Registry().destroy(m_entityId);
			m_entityId = entt::null;
		}
	}

	Ref<Entity> Entity::AddChild()
	{
		Ref<Entity> child = NewRef<Entity>(m_owner, this);
		m_children.push_back(child);

		return child;
	}

	void Entity::RemoveChild(Ref<Entity> child)
	{
		auto it = std::find(m_children.begin(), m_children.end(), child);
		if (it != m_children.end())
		{
			(*it)->RemoveAllChildren();
			m_children.erase(it);
		}
		else
			Log::Error(LogType::ECS, "Child entity not found");
	}

	void Entity::RemoveAllChildren()
	{
		for (auto& child : m_children)
		{
			child->RemoveAllChildren();
			child = nullptr;
		}
		m_children.clear();
	}
}