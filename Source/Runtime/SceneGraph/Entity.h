/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/SceneGraph/IComponent.h>

#include <entt/entt.hpp>

namespace Strand
{
	class Scene;

	class Entity
	{
	public:
		Entity(const String& entityName, Scene* scene, Entity* pParent = nullptr);
		~Entity() = default;

		i32 GetId() const { return m_id; }
		const String& GetName() const { return m_name; }
		void SetName(const String& newName) { m_name = newName; }

		b8 IsActive() const { return m_isActive; }
		void SetActive(b8 active) { m_isActive = active; }

		Entity* GetParent() const { return m_parent; }
		Scene* GetScene() const { return m_ownerScene; }

		void AddChild(const String& name);
		void RemoveChild(i32 childId);
		Entity* FindChild(const String& childName);
		Entity* GetChild(usize index) const;

		const Vector<Ref<Entity>>& GetChildren() const { return m_children; }
		usize GetCount() const { return m_children.size(); }

		template<typename T, typename... Args>
		void AddComponent(Args&&... args)
		{
			static_assert(std::is_base_of<IComponent, T>::value, "T must inherit from IComponent");
			Ref<T> component = MakeRef<T>(std::forward<Args>(args)...);
			component->SetEnabled(true);
			component->m_componentName = typeid(T).name();
			m_components.push_back(component);
		}

		template<typename T>
		T* GetComponent()
		{
			static_assert(std::is_base_of<IComponent, T>::value, "T must inherit from IComponent");
			for (const auto& component : m_components)
			{
				if (auto casted = dynamic_cast<T*>(component.get()))
					return casted;
			}
			return nullptr;
		}

		IComponent* GetComponent(const String& compName)
		{
			for (const auto& component : m_components)
			{
				if (component->GetComponentName() == compName)
					return component.get();
			}
			return nullptr;
		}

	private:
		static i32 m_nextId;
		i32 m_id;
		String m_name;
		b8 m_isActive;
		Scene* m_ownerScene;
		Entity* m_parent;
		Vector<Ref<Entity>> m_children;
		Vector<Ref<IComponent>> m_components;
	};
}