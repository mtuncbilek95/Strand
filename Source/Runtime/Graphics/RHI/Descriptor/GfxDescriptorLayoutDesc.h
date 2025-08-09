/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Util/DescriptorFormat.h>
#include <Runtime/Graphics/RHI/Util/ShaderStage.h>

namespace Strand
{
    struct DescriptorBinding
    {
        u32 binding;
        DescriptorType type;
        u32 count;
        ShaderStage stage;

        DescriptorBinding& setBinding(u32 index) { binding = index; return *this; }
        DescriptorBinding& setType(DescriptorType descriptorType) { type = descriptorType; return *this; }
        DescriptorBinding& setCount(u32 descriptorCount) { count = descriptorCount; return *this; }
        DescriptorBinding& setStage(ShaderStage shaderStage) { stage = shaderStage; return *this; }
    };

    struct GfxDescriptorLayoutDesc
    {
        Vector<DescriptorBinding> bindings;
        DescriptorLayoutFlags flags;

        GfxDescriptorLayoutDesc& addBinding(const DescriptorBinding& binding) { bindings.push_back(binding); return *this; }
        GfxDescriptorLayoutDesc& setFlags(DescriptorLayoutFlags f) { flags = f; return *this; }
    };

}
