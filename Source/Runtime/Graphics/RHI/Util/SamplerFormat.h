/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>

namespace Strand
{
	enum class SamplerFilter
	{
		Nearest,
		Linear,
		Cubic
	};

	enum class SamplerMipMap
	{
		Nearest,
		Linear
	};

	enum class SamplerAddress
	{
		Repeat,
		MirroredRepeat,
		ClampToEdge,
		ClampToBorder,
		MirrorClampToEdge
	};

	enum class BorderColor
	{
		TransparentBlack_Float,
		TransparentBlack_Int,
		OpaqueBlack_Float,
		OpaqueBlack_Int
	};
}
