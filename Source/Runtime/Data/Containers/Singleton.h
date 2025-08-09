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
