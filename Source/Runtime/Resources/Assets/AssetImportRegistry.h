/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Resources/Assets/IAssetImporter.h>

namespace Flax
{
	class AssetImportRegistry : public Singleton<AssetImportRegistry>
	{
	public:
		template<typename T, typename = std::enable_if_t<std::is_base_of_v<IAssetImporter, T>>>
		void RegisterImporter()
		{
			u32 typeId = GetUniqueTypeId<T>();

			if (m_importers.find(typeId) != m_importers.end())
			{
				Log::Error(LogType::Asset, "Importer '{}' is already registered.", TypeUtil::TypeName<T>());
				return;
			}

			m_importers[typeId] = NewRef<T>();
		}

		template<typename T, typename = std::enable_if_t<std::is_base_of_v<IAssetImporter, T>>>
		Ref<T> Importer()
		{
			u32 typeId = GetUniqueTypeId<T>();
			auto it = m_importers.find(typeId);
			if (it != m_importers.end())
				return std::dynamic_pointer_cast<T>(it->second);
			
			Log::Error(LogType::Asset, "Importer for type '{}' is not registered.", typeId);
			return nullptr;
		}

	private:
		HashMap<u32, Ref<IAssetImporter>> m_importers;
	};
}
