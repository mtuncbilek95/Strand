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
		Log::Debug(LogType::ECS, "Destroying entity with name {}", m_name);

		if (m_parent)
		{
			m_owner->Registry().destroy(m_entityId);
			m_entityId = entt::null;
		}
	}

	Entity* Entity::AddChild()
	{
		Ref<Entity> child = NewRef<Entity>(m_owner, this);
		m_children.push_back(child);

		return child.get();
	}

	void Entity::RemoveChild(Entity* child)
	{
		if (!child)
			return;

		String name = child ? child->Name() : "nullptr";
		usize targetIndex = IndexOf(child);

		if (targetIndex == NumericLimits<usize>::max())
		{
			Log::Warn(LogType::ECS, "Attempted to remove an entity that is not a child of the parent entity.");
			return;
		}

		m_children[targetIndex]->RemoveAllChildren();
		m_children.erase(m_children.begin() + targetIndex);

		Log::Debug(LogType::ECS, "Removing child entity with name {}", name);
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

	void Entity::MoveTo(Entity* target, Entity* parent)
	{
		if (target == this || target == nullptr || parent == nullptr)
			return;

		usize targetIndex = IndexOf(target);
		if (targetIndex == NumericLimits<usize>::max())
		{
			Log::Warn(LogType::ECS, "Attempted to move an entity that is not a child of the parent entity.");
			return;
		}

		if (parent == this)
		{
			Log::Warn(LogType::ECS, "Attempted to move an entity to its own parent.");
			return;
		}

		Ref<Entity> targetRef = m_children[targetIndex];
		m_children.erase(m_children.begin() + targetIndex);

		parent->m_children.push_back(targetRef);
		target->m_parent = parent;
	}

    usize Entity::IndexOf(Entity* child) const
    {
		for (usize i = 0; i < m_children.size(); ++i)
		{
			if (m_children[i].get() == child)
				return i;
		}

		return NumericLimits<usize>::max();
    }
}