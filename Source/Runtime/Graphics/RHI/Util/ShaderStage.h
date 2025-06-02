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
	enum class ShaderStage
	{
		Vertex = 1 << 0,
		TessControl = 1 << 1,
		TessEval = 1 << 2,
		Geometry = 1 << 3,
		Fragment = 1 << 4,
		Compute = 1 << 5,
		Raygen = 1 << 6,
		Anyhit = 1 << 7,
		ClosestHit = 1 << 8,
		Miss = 1 << 9,
		Intersection = 1 << 10,
		Callable = 1 << 11,
		Task = 1 << 12,
		Mesh = 1 << 13,
		All = 0x3FFF
	};
}
