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
	enum class ImageFormat : usize
	{
		Unknown,

		R8G8B8A8_UNorm_SRGB,
		R8G8B8A8_UNorm,
		R8G8B8A8_SNorm,
		R8G8B8A8_UInt,
		R8G8B8A8_SInt,
		R8G8B8A8_Float,

		R16G16B16A16_UNorm_SRGB,
		R16G16B16A16_UNorm,
		R16G16B16A16_SNorm,
		R16G16B16A16_UInt,
		R16G16B16A16_SInt,
		R16G16B16A16_Float,

		R32G32B32A32_UNorm,
		R32G32B32A32_SNorm,
		R32G32B32A32_UInt,
		R32G32B32A32_SInt,
		R32G32B32A32_Float,

		R8G8B8_UNorm,
		R8G8B8_SNorm,
		R8G8B8_UInt,
		R8G8B8_SInt,
		R8G8B8_Float,

		R16G16B16_UNorm,
		R16G16B16_SNorm,
		R16G16B16_UInt,
		R16G16B16_SInt,
		R16G16B16_Float,

		R32G32B32_UInt,
		R32G32B32_SInt,
		R32G32B32_Float,

		R8G8_UNorm,
		R8G8_SNorm,
		R8G8_UInt,
		R8G8_SInt,
		R8G8_Float,
		
		R16G16_UNorm,
		R16G16_SNorm,
		R16G16_UInt,
		R16G16_SInt,
		R16G16_Float,
		
		R32G32_UInt,
		R32G32_SInt,
		R32G32_Float,

		R8_UNorm,
		R8_SNorm,
		R8_UInt,
		R8_SInt,
		R8_Float,

		R16_UNorm,
		R16_SNorm,
		R16_UInt,
		R16_SInt,
		R16_Float,

		R32_UInt,
		R32_SInt,
		R32_Float,

		D32_Float
	};
}
