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
	/**
	 * @class Singleton
	 * @brief Singleton class with CRTP usage.
	 */
	template<typename T>
	class Singleton
	{
	public:
		static T& Get()
		{
			static T instance;
			return instance;
		}
	};
}
