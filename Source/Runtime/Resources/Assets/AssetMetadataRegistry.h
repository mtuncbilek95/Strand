/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Resources/Assets/AssetMetadataDesc.h>
#include <Runtime/Resources/Assets/AssetMetadata.h>

namespace Flax
{
	class AssetMetadataRegistry : public Singleton<AssetMetadataRegistry>
	{
	public:
		template<typename T, typename = std::enable_if_t<std::is_base_of_v<IAssetMetaExtension, T>>>
		void RegisterMetaExtension(const String& assetType, const String& extension)
		{
			if (m_metaExtensions.find(assetType) == m_metaExtensions.end())
				m_metaExtensions[assetType] = []() { return NewRef<T>(); };

			if (!extension.empty())
			{
				u32 hashExt = Hash<String>()(extension);
				m_assetTypeFromExt[hashExt] = assetType;
				Log::Info(LogType::Asset, "Registered extension '{}' for asset '{}'", extension, assetType);
			}

			Log::Info(LogType::Asset, "Registered meta extension for asset type '{}'", assetType);
		}

		Ref<AssetMetadata> CreateMetadata(const String& assetType, const AssetMetadataDesc& desc)
		{
			Ref<AssetMetadata> metadata = NewRef<AssetMetadata>();
			metadata->assetGuid = UuidHelper::GenerateID();
			metadata->assetName = desc.assetName;
			metadata->assetPath = desc.dstPath;
			metadata->assetType = assetType;
			metadata->lastModifiedDate = desc.lastModifiedDate;

			auto it = m_metaExtensions.find(assetType);
			if (it != m_metaExtensions.end())
			{
				metadata->metaExtension = it->second();
				metadata->metaExtension->InfoInternal(desc.srcPath);
			}
			else
				Log::Warn(LogType::Asset, "No meta extension registered for asset type '{}'", assetType);

			return metadata;
		}

		String AssetTypeFromExt(const String& ext)
		{
			u32 hashExt = Hash<String>()(ext);
			auto it = m_assetTypeFromExt.find(hashExt);
			if (it != m_assetTypeFromExt.end())
				return it->second;

			Log::Warn(LogType::Asset, "No asset type registered for extension '{}'", ext);
			return String();
		}

	private:
		HashMap<String, function<Ref<IAssetMetaExtension>()>> m_metaExtensions;
		Map<u32, String> m_assetTypeFromExt;
	};
}