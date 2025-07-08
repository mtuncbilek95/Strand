/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Data/Containers/Singleton.h>
#include <entt/entt.hpp>

using namespace entt::literals;

#define F_OBJECT(type) \
	friend struct type##_Reflection

namespace Flax
{
	class MetaReflection : public Singleton<MetaReflection>
	{
	public:
		template<typename T>
		T* Construct()
		{
			auto type = entt::resolve<T>();
			auto inst = type.construct();

			return inst.try_cast<T>();
		}
	};
}
