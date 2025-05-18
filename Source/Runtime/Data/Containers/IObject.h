/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Data/Containers/Uuid.h>

namespace Flax
{
    /*
     * @class IObject
     * @brief Backbone definition of the every engine related class. Which
     * means that every object that inherits from IObject has its their own
     * GUID value.
     */
	class IObject
	{
	public:
		virtual ~IObject() = default;
	};
}