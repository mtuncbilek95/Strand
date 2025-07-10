/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>

namespace Flax
{
	class IAssetImporter;

	class AssetService : public RuntimeServiceBase
	{
	public:
		AssetService();
		~AssetService();

		/* Don't use if you dont know what you're doing. */
		template<typename T, typename = std::enable_if_t<std::is_base_of_v<IAssetImporter, T>>>
		void RegisterImporter(const String& extensionType)
		{
			if (m_importers.find(extensionType) != m_importers.end())
			{
				Log::Error(LogType::Asset, "Importer for type '{}' is already registered.", TypeUtil::TypeName<T>());
				return;
			}

			auto importer = NewRef<T>();
			m_importers[extensionType] = importer;
		}

		void LoadSync(const Path& path);
		void LoadAsync(const Path& path);
		void UnloadSync(const Path& path);
		void UnloadAsync(const Path& path);
		void UnloadAll();

		void ImportToProject(const Path& srcPath, const Path& dstPath);
		void ImportToProjectAsync(const Path& srcPath, const Path& dstPath);

		void ResetServiceField() override final;

	private:
		HashMap<String, Ref<IAssetImporter>> m_importers;
	};
}
