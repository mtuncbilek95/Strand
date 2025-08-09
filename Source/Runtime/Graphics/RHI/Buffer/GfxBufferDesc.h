/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Util/BufferFormat.h>
#include <Runtime/Graphics/RHI/Util/MemoryFormat.h>

namespace Strand
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
