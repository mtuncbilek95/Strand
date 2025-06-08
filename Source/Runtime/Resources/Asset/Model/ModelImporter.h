/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Resources/Asset/Core/IAssetImporter.h>

namespace Flax
{
	class ModelImporter final : public IAssetImporter
	{
	public:
		ModelImporter() = default;
		~ModelImporter() override final;

		String AssetTypeName() const override final { return "model"; }
		u32 AssetTypeID() const override final;
		void Import(const String& sourcePath, AssetMetadata& outMetadata) override final;
	};
}
