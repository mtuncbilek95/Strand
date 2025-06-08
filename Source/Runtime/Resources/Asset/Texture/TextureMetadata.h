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
    struct TextureMetadata : public IAssetMetadataExtension
    {
        Math::Vec2u size;
        String format;

        void Serialize(const Json& jsonOut) override final;
        void Deserialize(const Json& jsonIn) override final;
    };
}