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
#include <Runtime/Graphics/RHI/Util/ImageFormat.h>

namespace Flax
{
	struct TextureMetaExtension : public IAssetMetaExtension
	{
		Math::Vec3u imageSize;
		ImageFormat imageFormat;
		u32 mipLevels;
		u32 arrayLayers;

		void Serialize(Toml& tomlOut) override;
		void Deserialize(const Toml& tomlIn) override;

	protected:
		void InfoInternal(const Path& assetPath) override;
	};
}
