/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>

#include <entt/entt.hpp>

namespace Flax
{
	class ComponentResolver;
	class Entity;
	class IComponentBase;

	class Scene
	{
		friend class ComponentResolver;

	public:
		Scene();
		~Scene();

		Ref<Entity> AddEntity(Ref<Entity> parent = nullptr);
		void RemoveEntity(Ref<Entity> entity);

		entt::registry& Registry() { return m_registry; }

	private:
		entt::registry m_registry;
		Ref<Entity> m_rootEntity;
	};
}