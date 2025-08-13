/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Data/Definitions/Definitions.h>
#include <Runtime/Data/Definitions/StdNames.h>
#include <Runtime/Logger/Logger.h>

namespace Strand
{
	class Service
	{
	public:
		virtual ~Service() = default;

	public:
		virtual void InitializeServiceField() = 0;
		virtual void ResetServiceField() = 0;
	};
}
