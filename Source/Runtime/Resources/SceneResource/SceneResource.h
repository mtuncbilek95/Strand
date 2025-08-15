/*
 * Licensed under the terms specified in the LICENSE.md file
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Resources/ResourceBase.h>
#include <Runtime/SceneGraph/Scene.h>

namespace Strand
{
	STRAND_CLASS();
	class SceneResource : public ResourceBase
	{
		STRAND_OBJECT(SceneResource);
	public:
		SceneResource(const ResourceDesc& desc, const String& sceneName);
		~SceneResource() override;

		const String& GetSceneName() const { return m_sceneName; }
		void SetSceneName(const String& name) { m_sceneName = name; }

		Scene* GetScene() const { return m_scene.get(); }
		void SetScene(Ref<Scene> scene) { m_scene = std::move(scene); }

	private:
		STRAND_FIELD();
		String m_sceneName;
		STRAND_FIELD();
		Ref<Scene> m_scene;
	};
}