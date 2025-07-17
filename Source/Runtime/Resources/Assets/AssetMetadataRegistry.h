/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Resources/Assets/AssetMetadata.h>

namespace Flax
{
	class AssetMetadataRegistry : public Singleton<AssetMetadataRegistry>
	{
	public:
		template<typename T, typename = std::enable_if_t<std::is_base_of_v<IAssetMetaExtension, T>>>
		void RegisterMetaExtension(const String& assetType)
		{
			if (m_metaExtensions.find(assetType) != m_metaExtensions.end())
			{
				Log::Error(LogType::Asset, "Meta extension for type '{}' is already registered.", assetType);
				return;
			}
			m_metaExtensions[assetType] = []() { return NewRef<T>(); };
			Log::Info(LogType::Asset, "Registered meta extension for asset type '{}'", assetType);
		}

		Ref<AssetMetadata> CreateEmptyMetadata(const String& assetType)
		{
			Ref<AssetMetadata> metadata = NewRef<AssetMetadata>();
			metadata->assetType = assetType;
			auto it = m_metaExtensions.find(assetType);
			if (it != m_metaExtensions.end())
				metadata->metaExtension = it->second();
			else
				Log::Warn(LogType::Asset, "No meta extension registered for asset type '{}'", assetType);

			return metadata;
		}

	private:
		HashMap<String, function<Ref<IAssetMetaExtension>()>> m_metaExtensions;
	};
}
