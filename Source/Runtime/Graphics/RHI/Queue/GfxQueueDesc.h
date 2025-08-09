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
	enum class QueueType
	{
		Graphics,
		Compute,
		Transfer,
		Sparse
	};

	struct GfxQueueDesc
	{
		QueueType type;
		u32 familyIndex;

		GfxQueueDesc& setType(QueueType t) { type = t; return *this; }
		GfxQueueDesc& setIndex(u32 index) { familyIndex = index; return *this; }
	};
}
