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
    class GfxObject;
    class GfxDescriptorLayout;
    class GfxDescriptorPool;

    struct GfxDescriptorSetDesc
    {
        GfxDescriptorLayout* layout;
        GfxDescriptorPool* pool;

        GfxDescriptorSetDesc& setLayout(GfxDescriptorLayout* l) { layout = l; return *this; }
        GfxDescriptorSetDesc& setPool(GfxDescriptorPool* p) { pool = p; return *this; }
    };

    struct UpdateEntry
    {
        GfxObject* resource;
        GfxObject* sampler;

        DescriptorType type;
        u32 count;
        u32 arrayElement;
        u32 bufferOffset;
        u32 binding;

        UpdateEntry& setResource(GfxObject* r) { resource = r; return *this; }
        UpdateEntry& setSampler(GfxObject* s) { sampler = s; return *this; }
        UpdateEntry& setType(DescriptorType t) { type = t; return *this; }
        UpdateEntry& setCount(u32 c) { count = c; return *this; }
        UpdateEntry& setArrayElement(u32 a) { arrayElement = a; return *this; }
        UpdateEntry& setBufferOffset(u32 offset) { bufferOffset = offset; return *this; }
        UpdateEntry& setBinding(u32 b) { binding = b; return *this; }
    };

    struct GfxSetUpdateDesc
    {
        Vector<UpdateEntry> entries;

        GfxSetUpdateDesc& addEntry(const UpdateEntry& e) { entries.push_back(e); return *this; }
    };

}
