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
	struct IAssetMetadataExtension
	{
		virtual ~IAssetMetadataExtension() = default;

		virtual void Serialize(const Json& jsonOut) = 0;
		virtual void Deserialize(const Json& jsonIn) = 0;
	};

	struct AssetMetadata
	{
		String name;
		String type;
		String path;
		Uuid assetId;

		Ref<IAssetMetadataExtension> extension;

		void Serialize(Json& jsonOut) const;
		void Deserialize(const Json& jsonIn);
	};
}
