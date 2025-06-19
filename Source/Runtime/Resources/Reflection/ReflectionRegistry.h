/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Resources/Reflection/IReflectable.h>

namespace Flax
{
	class ReflectionRegistry : public Singleton<ReflectionRegistry>
	{
	public:
		void RegisterType(const String& typeName, function<IReflectable* ()> creator);
		IReflectable* CreateInstance(const )
	};
}
