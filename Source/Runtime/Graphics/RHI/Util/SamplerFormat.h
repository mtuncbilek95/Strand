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
