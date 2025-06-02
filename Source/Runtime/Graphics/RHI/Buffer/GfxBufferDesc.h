/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Util/BufferFormat.h>
#include <Runtime/Graphics/RHI/Util/MemoryFormat.h>

namespace Flax
{
	struct GfxBufferDesc
	{
		usize sizeInBytes = 0;
		BufferUsage usage = BufferUsage::Uniform;

		MemoryUsage memUsage = MemoryUsage::AutoPreferHost;
		MemoryAllocation allocFlags = MemoryAllocation::Mapped;

		GfxBufferDesc& SetSize(usize size) { sizeInBytes = size; return *this; }
		GfxBufferDesc& SetUsage(BufferUsage u) { usage = u; return *this; }
		GfxBufferDesc& SetMemoryUsage(MemoryUsage mem) { memUsage = mem; return *this; }
		GfxBufferDesc& SetAllocationFlags(MemoryAllocation flags) { allocFlags = flags; return *this; }
	};
}
