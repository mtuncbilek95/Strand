/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Resources/Asset/Core/AssetTypeId.h>
#include <Runtime/Resources/Asset/Core/AssetMetadata.h>
#include <Runtime/Resources/Asset/Core/IAssetImporter.h>

namespace Flax
{
	struct AssetTypeInfo
	{
		u32 infoId;
		String name;
		function<Ref<IAssetMetadataExtension>()> CreateExtension;
		function<Ref<IAssetImporter>()> CreateImporter;
	};

	class AssetTypeRegistry : public Singleton<AssetTypeRegistry>
	{
	public:
		void RegisterType(const String& name, const AssetTypeInfo& info);
		const AssetTypeInfo* TypeInfo(const String& name);
		const AssetTypeInfo* TypeInfo(u32 typeId);
		
	private:
		HashMap<u32, AssetTypeInfo> m_registry;
		HashMap<String, u32> m_nameId;
		HashMap<u32, String> m_idName;
	};
}
