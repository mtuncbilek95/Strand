/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Data/Definitions/StdNames.h>

namespace Flax
{
	static Atomic<i32> uniqueTypeID;

	template<typename T>
	static i32 UniqueTypeId()
	{
		static const i32 id = uniqueTypeID++;
		return id;
	}
}