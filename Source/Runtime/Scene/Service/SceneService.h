/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Scene/Scene.h>

namespace Flax
{
	class SceneService final : public RuntimeServiceBase
	{
	public:
		SceneService() = default;
		~SceneService() = default;

		void SetCurrentScene(Scene* currentScene) { m_currentScene = currentScene; }
		Ref<Scene> LoadSceneFromFile(const String& path);
		Scene* GetCurrentScene() const { return m_currentScene; }

		void ResetServiceField() override final {}

	private:
		Scene* m_currentScene;
	};
}
