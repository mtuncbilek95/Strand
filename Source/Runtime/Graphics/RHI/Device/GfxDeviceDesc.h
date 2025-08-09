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
	struct GfxDeviceDesc
	{
		u32 graphicsQueueCount;
		u32 computeQueueCount;
		u32 transferQueueCount;

		GfxDeviceDesc& setGraphicsQueueCount(u32 count) { graphicsQueueCount = count; return *this; }
		GfxDeviceDesc& setComputeQueueCount(u32 count) { computeQueueCount = count; return *this; }
		GfxDeviceDesc& setTransferQueueCount(u32 count) { transferQueueCount = count; return *this; }
	};
}
