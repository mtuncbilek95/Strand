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
	enum class TopologyType
	{
		Unknown,
		PointList,
		LineList,
		LineStrip,
		TriangleList,
		TriangleStrip,
		TriangleFan
	};

	enum class PolygonType
	{
		Unknown,
		Fill,
		Line,
		Point
	};

	enum class CullMode
	{
		Unknown,
		Front,
		Back
	};

	struct RasterizationDesc
	{
		b8 depthBias = false;
		f32 depthBiasFactor = 0.0f;
		f32 depthBiasClamp = 1.0f;
		f32 depthBiasSlope = 0.0f;
		PolygonType polygonType = PolygonType::Fill;
		CullMode cullMode = CullMode::Back;
		b8 isClockWise = true;
	};
}
