/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Resources/Asset/Core/AssetMetadata.h>

namespace Flax
{
	struct MetaTypeInfo
	{
		String typeName;
		function<Ref<AssetMetadata>()> createInstance;
	};

	class MetadataRegistry : public Singleton<MetadataRegistry>
	{
	public:
		template<typename T, typename = std::enable_if_t<std::is_base_of_v<AssetMetadata, T>>>
		void RegisterMetaType()
		{
			MetaTypeInfo newInfo =
			{
				.typeName = T::StaticAssetType(),
				.createInstance = [] { return NewRef<T>(); }
			};

			m_registry[TypeIndex(typeid(T))] = newInfo;

			Log::Debug(LogType::Asset, "MetaTypeInfo '{}' has been registered", newInfo.typeName);
		}

		template<typename T, typename = std::enable_if_t<std::is_base_of_v<AssetMetadata, T>>>
		MetaTypeInfo& MetaType()
		{
			auto it = m_registry.find(TypeIndex(typeid(T)));

			if (it == m_registry.end())
				throw std::runtime_error("MetaType not registered for type!");

			return it->second;
		}

	private:
		HashMap<TypeIndex, MetaTypeInfo> m_registry;
	};
}
