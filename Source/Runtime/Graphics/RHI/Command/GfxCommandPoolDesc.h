/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Util/CommandFormat.h>

namespace Strand
{
	class GfxQueue;

	struct GfxCommandPoolDesc
	{
		GfxQueue* queue = nullptr;
		CommandPoolFlags flags;

		GfxCommandPoolDesc& setQueue(GfxQueue* q) { queue = q; return *this; }
		GfxCommandPoolDesc& setFlags(CommandPoolFlags flag) { flags = flag; return *this; }
	};
}
