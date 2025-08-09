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
