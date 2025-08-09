/*
 * Licensed under the terms specified in the LICENSE.md file
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Data/Definitions/StdNames.h>

namespace Strand
{
	static Atomic<i32> uniqueTypeID;

	template<typename T>
	static i32 UniqueTypeId()
	{
		static const i32 id = uniqueTypeID++;
		return id;
	}
}