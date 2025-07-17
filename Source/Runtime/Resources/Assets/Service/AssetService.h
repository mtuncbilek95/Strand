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
	class AssetImportRegistry;
	class AssetMetadataRegistry;

	class AssetService : public RuntimeServiceBase
	{
	public:
		AssetService();
		~AssetService();

		void ImportAsset(const Path& virtualPath);

		void ResetServiceField() override final;

	private:
		AssetImportRegistry* m_importReg;
		AssetMetadataRegistry* m_metaReg;
	};
}
