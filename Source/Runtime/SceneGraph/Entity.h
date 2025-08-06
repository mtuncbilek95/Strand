/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
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