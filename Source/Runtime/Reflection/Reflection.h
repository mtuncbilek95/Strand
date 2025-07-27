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
	class Reflection
	{
	public:
		template<typename T>
		static Vector<String> FieldNames(const T& obj)
		{
			return FieldNames(T::StaticClassName());
		}

		static Vector<String> FieldNames(const String& className)
		{
			auto classInfo = ReflectionRegistry::GetClass(className);
			if (!classInfo)
				return Vector<String>();

			Vector<String> fieldNames;
			for (const auto& [fieldName, _] : classInfo->fields)
				fieldNames.emplace_back(fieldName);

			return fieldNames;
		}

		template<typename T>
		static Any GetFieldValue(const T& obj, const String& fieldName)
		{
			auto fieldInfo = ReflectionRegistry::GetField(T::StaticClassName(), fieldName);
			if (!fieldInfo)
				return Any();

			return fieldInfo->getter(const_cast<T*>(&obj));
		}

		template<typename T>
		static b8 SetFieldValue(T& obj, const String& fieldName, const Any& value)
		{
			auto fieldInfo = ReflectionRegistry::GetField(T::StaticClassName(), fieldName);
			if (!fieldInfo)
				return false;

			try
			{
				fieldInfo->setter(&obj, value);
				return true;
			}
			catch (...)
			{
				Log::Error(LogType::Engine, "Failed to set field '{}' in class '{}'.", fieldName, T::StaticClassName());
				return false;
			}
		}

		template<typename T>
		static Ref<T> CreateInstance()
		{
			auto classInfo = ReflectionRegistry::GetClass(T::StaticClassName());
			if (!classInfo)
				return nullptr;

			auto instance = classInfo->constructor();
			return std::static_pointer_cast<T>(instance);
		}
	};

}

#define FLAX_OBJECT(ClassName) \
	friend struct ClassName##_ReflectionRegister; \
public: \
	static String StaticClassName() \
	{ \
		static String sName = #ClassName; \
		return sName; \
	} \
private:

#define BEGIN_REFLECT_CLASS(ClassName) \
    struct ClassName##_ReflectionRegister { \
        ClassName##_ReflectionRegister() { \
            ClassInfo classInfo; \
            classInfo.className = #ClassName; \
            classInfo.size = sizeof(ClassName); \
            \
            classInfo.constructor = []() -> Owned<ObjectBase> { \
                return NewOwn<ClassName>(); \
            };

#define REFLECT_FIELD(ClassName, FieldName) \
		{ \
			FieldInfo fieldInfo; \
			fieldInfo.fieldName = #FieldName; \
			fieldInfo.typeName = typeid(decltype(ClassName##::FieldName)).name(); \
			fieldInfo.typeHash = typeid(decltype(ClassName##::FieldName)).hash_code(); \
			\
			fieldInfo.getter = [](void* obj) -> Any { \
				auto* instance = static_cast<ClassName*>(obj); \
				return instance->FieldName; \
			};\
			\
			fieldInfo.setter = [](void* obj, const Any& value) { \
                    auto* instance = static_cast<ClassName*>(obj); \
                    using FieldType = decltype(instance->FieldName); \
                    instance->FieldName = std::any_cast<FieldType>(value); \
                }; \
                \
            classInfo.fields[#FieldName] = std::move(fieldInfo); \
		}

#define END_REFLECT_CLASS(ClassName) \
            ReflectionRegistry::DefineClass(#ClassName, std::move(classInfo)); \
        } \
    }; \
    \
    static ClassName##_ReflectionRegister ClassName##RegisterInstance;
