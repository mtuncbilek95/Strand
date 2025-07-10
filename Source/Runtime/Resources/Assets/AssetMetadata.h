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
	struct IAssetMetaExtension
	{
		virtual ~IAssetMetaExtension() = default;

		virtual void Serialize(Toml& tomlOut) = 0;
		virtual void Deserialize(const Toml& tomlIn) = 0;
	};

	struct AssetMetadata
	{
		String assetName;
		String assetType;
		Path assetPath;
		usize assetSize;
		DateTime lastModifiedDate;

		Owned<IAssetMetaExtension> metaExtension;

		void Serialize(Toml& tomlOut) const;
		void Deserialize(const Toml& tomlIn);
	};
}
