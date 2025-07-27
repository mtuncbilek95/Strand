/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Reflection/ReflectionRegistry.h>

namespace Flax
{
	class JsonSerializer
	{
	public:
		template<typename T, typename = std::enable_if_t<std::is_base_of_v<ObjectBase, T>>>
		static void Serialize(const T& obj, OrderedJson& jsonOut)
		{
			SerializeImpl(&obj, T::StaticClassName(), jsonOut);
		}

		template<typename T, typename = std::enable_if_t<std::is_base_of_v<ObjectBase, T>>>
		static void Deserialize(const OrderedJson& jsonIn, T& obj)
		{
			DeserializeImpl(jsonIn, &obj, T::StaticClassName());
		}

	private:
		static void SerializeImpl(const void* obj, const String& objName, OrderedJson& jsonOut);
		static void DeserializeImpl(const OrderedJson& jsonIn, void* obj, const String& objName);
	};
}