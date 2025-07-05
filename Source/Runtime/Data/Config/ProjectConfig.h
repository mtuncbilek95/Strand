/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Data/Config/ProjectConfigDesc.h>

namespace Flax
{
	class ProjectConfig
	{
	public:
		const Uuid& ProjectId() const { return m_desc.projectId; }
		const String& ProjectName() const { return m_desc.projectName; }
		const Math::Vec3u& EngineVersion() const { return m_desc.engineVersion; }
		const DateTime& GenerateDate() const { return m_desc.generateDate; }
		const DateTime& LastModifiedDate() const { return m_desc.lastModifiedDate; }
		const String& Description() const { return m_desc.description; }
		GfxType GraphicsAPI() const { return m_desc.graphicsApi; }

		void LoadFrom(const String& projectPath);
		void SaveFile();

	private:
		ProjectConfigDesc m_desc;
		String m_projectPath;
	};
}
