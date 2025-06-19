/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Resources/Asset/Core/AssetImporter.h>

namespace Flax
{
	struct ImportTypeInfo
	{
		String typeName;
		String fileExtension;
		function<Ref<AssetImporter>()> createInstance;
	};

	class ImporterRegistry : public Singleton<ImporterRegistry>
	{
	public:
		template<typename T, typename = std::enable_if_t<std::is_base_of_v<AssetImporter, T>>>
		void RegisterImporter(const String& extension)
		{
			ImportTypeInfo newInfo =
			{
				.typeName = T::StaticAssetType(),
				.fileExtension = extension,
				.createInstance = [] { return NewRef<T>(); }
			};

			m_registry[TypeIndex(typeid(T))] = newInfo;

			Log::Debug(LogType::Asset, "ImportTypeInfo '{}' for '{}' has been registered", newInfo.typeName, newInfo.fileExtension);
		}

		template<typename T, typename = std::enable_if_t<std::is_base_of_v<AssetImporter, T>>>
		ImportTypeInfo& ImportType()
		{
			SharedLock readLock(m_mutex);
			auto it = m_registry.find(TypeIndex(typeid(T)));

			if (it == m_registry.end())
				throw std::runtime_error("ImportType not registered for type!");

			return it->second;
		}

	private:
		HashMap<TypeIndex, ImportTypeInfo> m_registry;
		SharedMutex m_mutex;
	};
}
