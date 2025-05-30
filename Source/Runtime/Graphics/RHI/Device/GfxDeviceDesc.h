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
