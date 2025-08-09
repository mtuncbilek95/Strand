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
	enum class BufferUsage
	{
		TransferSrc = 1 << 0,
		TransferDst = 1 << 1,
		UniformTexel = 1 << 2,
		StorageTexel = 1 << 3,
		Uniform = 1 << 4,
		Storage = 1 << 5,
		Index = 1 << 6,
		Vertex = 1 << 7,
		Indirect = 1 << 8,
		VideoDecodeSrc = 1 << 9,
		VideoDecodeDst = 1 << 10
	};
}