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
#include <Runtime/Data/Containers/Singleton.h>
#include <Runtime/Logger/Logger.h>
#include <Runtime/Reflection/ReflectionRegistry.h>

namespace Flax
{
#define FLAX_OBJECT(ClassName) \
	private: \
		friend class TypeAccessor<ClassName>; \
		static String StaticClassName() \
		{ \
			String func = __FUNCTION__; \
			usize index = func.find(':'); \
			return func.substr(0, index); \
		} \
	public:

#define FLAX_CLASS(...)
#define FLAX_ENUM(...)
#define FLAX_FIELD(...)
#define FLAX_METHOD(...)
}