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
#include <Runtime/Reflection/TypeInfo.h>
#include <Runtime/Reflection/FieldInfo.h>
#include <Runtime/Reflection/ClassInfo.h>

namespace Flax
{
	class ReflectionRegistry : public Singleton<ReflectionRegistry>
	{
	public:
		template<typename T>
		void RegisterReflectionType()
		{
			auto& typeID = typeid(T);
			auto it = m_typeRegistry.find(typeID.hash_code());
			if (it != m_typeRegistry.end())
			{
				Log::Warn(LogType::Reflection, "'{}' -- '{}' has been already registered!", typeID.name(), typeID.hash_code());
				return;
			}

			TypeInfo info;
			info.typeName = typeID.name();
			info.typeHash = typeID.hash_code();
			info.typeSize = sizeof(T);
			info.category = FindCategory<T>();
			info.isConst = std::is_const<T>::value;
			info.isRef = std::is_reference<T>::value;
			
			m_typeRegistry[info.typeHash] = std::move(info);
			Log::Info(LogType::Reflection, "'{}' has been registered to runtime reflection with '{}' hash.", typeID.name(), typeID.hash_code());
		}
	private:
		template<typename T>
		TypeCategory FindCategory() { return TypeCategory::Struct; }

	private:
		HashMap<u32, TypeInfo> m_typeRegistry;
	};
}
