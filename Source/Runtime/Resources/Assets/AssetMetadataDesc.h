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
	struct AssetMetadataDesc
	{
		String assetName;
		Path srcPath;
		Path dstPath;
		DateTime lastModifiedDate;

		AssetMetadataDesc& setName(const String& name) { assetName = name; return *this; }
		AssetMetadataDesc& setSrcPath(const Path& path) { srcPath = path; return *this; }
		AssetMetadataDesc& setDstPath(const Path& path) { dstPath = path; return *this; }
		AssetMetadataDesc& setLastModifiedDate(const DateTime& date) { lastModifiedDate = date; return *this; }
	};
}
