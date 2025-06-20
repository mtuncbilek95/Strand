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
	struct ModelMetadata : public AssetMetadata
	{
		u32 meshCount;
		Vector<String> meshNames;

		static String StaticAssetType() { return "model"; }
		String AssetType() const override final { return StaticAssetType(); }
	};
}
