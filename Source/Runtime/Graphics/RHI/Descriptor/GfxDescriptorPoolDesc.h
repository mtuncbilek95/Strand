/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Util/DescriptorFormat.h>

namespace Strand
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
