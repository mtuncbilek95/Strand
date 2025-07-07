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
	namespace TypeUtil
	{
		template<typename T>
		String TypeName()
		{
			String funcSig = __FUNCSIG__;
			auto start = funcSig.find("TypeName<") + 9;
			auto end = funcSig.find(">(void)", start);
			return funcSig.substr(start, end - start);
		}

		template<typename T>
		u64 GetTypeHash()
		{
			return Hash<TypeIndex>{}(TypeIndex(typeid(T)));
		}
	}

	static Atomic<i32> uniqueTypeID;

	template<typename T>
	static i32 GetUniqueTypeId()
	{
		static const i32 id = uniqueTypeID++;
		return id;
	}
}