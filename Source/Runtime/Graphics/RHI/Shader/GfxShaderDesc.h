/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Util/ShaderStage.h>

namespace Strand
{
	struct GfxShaderDesc
	{
		ShaderStage stage;
		ReadArray<u32> byteCode;

		GfxShaderDesc& setStage(ShaderStage s) { stage = s; return *this; }
		GfxShaderDesc& setByteCode(const ReadArray<u32>& code) { byteCode = code; return *this; }
	};
}
