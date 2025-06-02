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
	enum class MemoryUsage
	{
		Unknown = 0,
		GpuLazy = 1 << 0,
		Auto = 1 << 1,
		AutoPreferDevice = 1 << 2,
		AutoPreferHost = 1 << 3
	};

	enum class MemoryAllocation
	{
		DedicatedMemory = 1 << 0,
		NeverAllocate = 1 << 1,
		Mapped = 1 << 2,
		UpperAddress = 1 << 3,
		DontBind = 1 << 4,
		WithinBudget = 1 << 5,
		CanAlias = 1 << 6,
		SequentialWrite = 1 << 7,
		HostAccessRandom = 1 << 8,
		AllowTransferInstead = 1 << 9,
		StrategyMinMemory = 1 << 10,
		StrategyMinTime = 1 << 11,
		StrategyMinOffset = 1 << 12,
		StrategyMask = StrategyMinMemory | 
		StrategyMinTime | StrategyMinOffset
	};
}