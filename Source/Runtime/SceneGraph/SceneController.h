/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>

namespace Strand
{
	class Scene;
	class Entity;
	class IComponent;

	class SceneController : public Service
	{
	public:
		void CreateNewScene(const String& sceneName) {}

		void InitializeServiceField() override final {}
		void ResetServiceField() override final {}

	private:
		Ref<Scene> m_scene;
	};
}