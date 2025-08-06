/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Serialization/SerializerHelpers.h>

namespace Strand
{
	class JsonSerializer : public Singleton<JsonSerializer>
	{
	public:
		template<HasStaticClassName T>
		void ToObject(T& object, const OrderedJson& jsonIn)
		{
			ToObjectImpl(T::StaticClassName(), ReflectionRegistry::Get().GetTypeInfo<T>().category, jsonIn);
		}

		template<HasStaticClassName T>
		void ToJson(const T& object, OrderedJson& jsonOut)
		{
			ToJsonImpl(T::StaticClassName(), ReflectionRegistry::Get().GetTypeInfo<T>().category, static_cast<void*>(object), jsonOut);
		}

	private:
		void ToObjectImpl(const String& objectName, TypeCategory type, const OrderedJson& jsonIn);
		void ToJsonImpl(const String& objectName, TypeCategory type, void* objectPtr, OrderedJson& jsonOut);
	};
}