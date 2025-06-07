/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Resource/Asset/Core/AssetTypeId.h>
#include <Runtime/Resource/Asset/Core/AssetMetadata.h>
#include <Runtime/Resource/Asset/Core/IAssetImporter.h>

namespace Flax
{
	struct AssetTypeInfo
	{
		u32 infoId;
		String name;
		function<Ref<IAssetMetadataExtension>()> CreateExtension;
		function<Ref<IAssetImporter>()> CreateImporter;
	};

	struct AssetTypeRegistry
	{
		static void RegisterType(const String& name, const AssetTypeInfo& info);
		static const AssetTypeInfo* TypeInfo(const String& name);
		static const AssetTypeInfo* TypeInfo(u32 typeId);
	};
}
