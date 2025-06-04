/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Util/CommandFormat.h>

namespace Flax
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
