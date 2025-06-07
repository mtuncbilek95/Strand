/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Resource/Asset/Core/IAssetImporter.h>

namespace Flax
{
	struct AssetImportRegistry
	{
		static void RegisterImporter(const String& fileExt, function<Ref<IAssetImporter>()> importer);
		static Ref<IAssetImporter> Importer(const String& fileExt);
	};
}
