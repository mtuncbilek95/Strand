/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Data/Definitions/Definitions.h>
#include <Runtime/Data/Definitions/StdNames.h>
#include <Runtime/Logger/Logger.h>

namespace Flax
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
