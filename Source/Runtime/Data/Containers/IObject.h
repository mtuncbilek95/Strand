/*
 * Licensed under the terms specified in the LICENSE.md file
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Data/Containers/Uuid.h>

namespace Strand
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