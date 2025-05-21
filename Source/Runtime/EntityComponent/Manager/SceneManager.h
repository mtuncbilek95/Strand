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

namespace Flax
{
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		SceneManager() = default;
		~SceneManager() = default;

		void SetCurrentScene(Scene* currentScene) { m_currentScene = currentScene; }
		Scene* GetCurrentScene() const { return m_currentScene; }

	private:
		Scene* m_currentScene;
	};
}
