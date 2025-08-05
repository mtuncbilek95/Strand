/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>

namespace Strand
{
	class Entity;

	class Scene
	{
	public:
		Scene(const String& sceneName);
		~Scene();

		const String& GetName() const { return m_name; }
		void SetName(const String& name) { m_name = name; }

		void AddChild(const String& name);
		void RemoveChild(i32 childId);
		Entity* FindChild(const String& childName);
		Entity* GetChild(usize index) const { return m_entities[index].get(); }

		const Vector<Ref<Entity>>& GetChildren() const { return m_entities; }
		usize GetCount() const { return m_entities.size(); }

	private:
		String m_name;
		Vector<Ref<Entity>> m_entities;
	};
}