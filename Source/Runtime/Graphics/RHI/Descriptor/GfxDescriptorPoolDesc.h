/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Util/DescriptorFormat.h>

namespace Flax
{
    struct PoolSize
    {
        DescriptorType type;
        u32 count;

        PoolSize& setType(DescriptorType t) { type = t; return *this; }
        PoolSize& setCount(u32 c) { count = c; return *this; }
    };

    struct GfxDescriptorPoolDesc
    {
        Vector<PoolSize> poolSize;
        u32 maxSets;
        DescriptorPoolFlags flags;

        GfxDescriptorPoolDesc& addPoolSize(const PoolSize& p) { poolSize.push_back(p); return *this; }
        GfxDescriptorPoolDesc& setMaxSets(u32 sets) { maxSets = sets; return *this; }
        GfxDescriptorPoolDesc& setFlags(DescriptorPoolFlags f) { flags = f; return *this; }
    };
 }
