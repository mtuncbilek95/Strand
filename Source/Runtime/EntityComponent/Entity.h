/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/EntityComponent/Scene.h>
#include <Runtime/EntityComponent/Component.h>

#include <entt/entt.hpp>

namespace Flax
{
	class Scene;
	class IComponentBase;

	class Entity
	{
	public:
		Entity(Scene* owner, Entity* parent = nullptr);
		~Entity();

		Ref<Entity> AddChild();
		void RemoveChild(Ref<Entity> child);
		void RemoveAllChildren();

		template<typename T, typename...Args, typename = std::enable_if<std::is_base_of_v<IComponentBase, T>>>
		void AddComponent(Args&&...)
		{
			if (m_components.find(T::StaticName()) == m_components.end())
			{
				auto component = GlobalComponentResolver::CreateComponent(T::StaticName());
				if (component)
				{
					m_owner->GetRegistry().emplace<T>(m_entityId, std::forward<Args>(args)...);

					m_components[T::StaticName()] = std::move(component);
					Log::Debug(LogType::ECS, "Adding component {} to entity", T::StaticName());
				}
			}
			else
				Log::Warn(LogType::ECS, "Component {} already exists", T::StaticName());
		}

		template<typename T>
		T* GetComponent(const String& name)
		{
			if (name.empty())
			{
				auto it = m_components.find(T::StaticName());
				if (it != m_components.end())
				{
					return static_cast<T*>(it->second.get());
				}
				Log::Error(LogType::ECS, "Component {} not found", T::StaticName());
				return nullptr;
			}
			else
			{
				auto it = m_components.find(name);
				if (it != m_components.end())
				{
					return static_cast<T*>(it->second.get());
				}

				Log::Error(LogType::ECS, "Component {} not found", name);
				return nullptr;
			}
		}

		entt::entity GetEntityId() const { return m_entityId; }
		usize GetEntitySize() const { return m_children.size(); }
		const Vector<Ref<Entity>>& GetChildren() const { return m_children; }

	private:
		Scene* m_owner = nullptr;
		Entity* m_parent = nullptr;
		Vector<Ref<Entity>> m_children;

		entt::entity m_entityId = entt::null;

		HashMap<String, Owned<IComponentBase>> m_components;
	};
}