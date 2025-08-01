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
		template<typename T, typename U = void>
		void RegisterClassInfo()
		{
			ClassInfo classInfo = {};

			classInfo.className = T::StaticClassName();
			classInfo.classHash = typeid(T).hash_code();
			classInfo.classSize = sizeof(T);
			classInfo.classAlignment = alignof(T);

			classInfo.constructors.clear();
			classInfo.constructorLookup.clear();
			classInfo.superClassNames.clear();
			classInfo.fields.clear();

			if constexpr (!std::is_void<U>::value)
				classInfo.firstSuperClass = U::StaticClassName();

			m_classRegistry[classInfo.classHash] = classInfo;
		}

		template<typename T, typename... Args>
		void RegisterConstructor()
		{
			String className = T::StaticClassName();
			u32 classHash = typeid(T).hash_code();
			ClassInfo& classInfo = m_classRegistry[classHash];

			ConstructorInfo ctorInfo = {};
			ctorInfo.parameterTypes = { GetTypeInfo<Args>()... };
			ctorInfo.parameterHash = GenerateParameterHash<Args...>();
			ctorInfo.constructorPtr = &ConstructorWrapper<T, Args...>;

			usize index = classInfo.constructors.size();
			classInfo.constructors.push_back(ctorInfo);
			classInfo.constructorLookup[ctorInfo.parameterHash] = index;
		}

		// TODO: Ignore Method for now I'm mentally tired
		/*
		 * template<typename T, typename... Args>
		 * void RegisterMethodInfo()
		 * {
		 * }
		 */

		template<typename T>
		void RegisterFieldInfo(const String& className, const String& fieldName, usize offset, const TypeInfo& typeInfo)
		{
			u32 classHash = typeid(T).hash_code();
			ClassInfo& classInfo = m_classRegistry[classHash];

			FieldInfo fieldInfo = {};
			fieldInfo.fieldName = fieldName;
			fieldInfo.fieldTypeInfo = typeInfo;
			fieldInfo.offset = offset;

			classInfo.fields[fieldName] = std::move(fieldInfo);
		}

		template<typename T>
		void RegisterTypeInfo()
		{
			auto& typeID = typeid(T);
			auto it = m_typeRegistry.find(typeID.hash_code());
			if (it != m_typeRegistry.end())
			{
				Log::Warn(LogType::Reflection, "'{}' has been registered already!", typeID.name());
				return;
			}

			TypeInfo info = {};
			info.typeName = typeID.name();
			info.typeHash = typeID.hash_code();
			info.typeSize = sizeof(T);
			info.isConst = std::is_const<T>::value;
			info.isRef = std::is_reference<T>::value;
			info.category = FindCategory<T>();
			
			m_typeRegistry[typeID.hash_code()] = std::move(info);
		}

		template<typename T>
		b8 IsTypeRegistered()
		{
			auto& typeID = typeid(T);
			auto it = m_typeRegistry.find(typeID.hash_code());
			if (it != m_typeRegistry.end())
				return true;

			return false;
		}

		template<typename T>
		b8 IsClassRegistered()
		{
			auto it = m_classRegistry.find(typeid(T).hash_code());
			if (it != m_classRegistry.end())
				return true;

			return false;
		}

		template<typename T>
		ClassInfo* GetClassInfo()
		{
			auto it = m_classRegistry.find(typeid(T).hash_code());
			if (it != m_classRegistry.end())
				return &it->second;

			return nullptr;
		}

		template<typename T>
		TypeInfo* GetTypeInfo()
		{
			auto it = m_typeRegistry.find(typeid(T).hash_code());
			if (it != m_typeRegistry.end())
				return &it->second;

			return nullptr;
		}

	private:
		template<typename T, typename... Args>
		static void* ConstructorWrapper(void* params)
		{
			return ConstructorWrapperImpl<T, Args...>(params, std::index_sequence_for<Args...>{});
		}

		template<typename T, typename... Args, usize... I>
		static void* ConstructorWrapperImpl(void* params, std::index_sequence<I...>)
		{
			return new T(ExtractParams<Args>(params, I)...);
		}

		template<typename... Args>
		u32 GenerateParameterHash()
		{
			String combined;
			((combined += String(typeid(Args).name()) + "|"), ...);
			return Hash<String>{}(combined);
		}

		template<typename T>
		T ExtractParams(void* params, usize index)
		{
			void** paramArray = static_cast<void**>(params);

			if (!paramArray || !paramArray[index])
				throw std::runtime_error("Invalid parameter");

			return *static_cast<T*>(paramArray[index]);
		}

		template<typename T>
		usize GetParamIndex() 
		{
			static usize index = 0;
			return index++;
		}

		template<typename T>
		TypeCategory FindCategory() 
		{
			if constexpr (std::is_same<T, b8>::value) return TypeCategory::Boolean;
			else if constexpr (std::is_same<T, c8>::value) return TypeCategory::Char;
			else if constexpr (std::is_same<T, i8>::value) return TypeCategory::Signed8;
			else if constexpr (std::is_same<T, i16>::value) return TypeCategory::Signed16;
			else if constexpr (std::is_same<T, i32>::value) return TypeCategory::Signed32;
			else if constexpr (std::is_same<T, i64>::value) return TypeCategory::Signed64;
			else if constexpr (std::is_same<T, u8>::value) return TypeCategory::Unsigned8;
			else if constexpr (std::is_same<T, u16>::value) return TypeCategory::Unsigned16;
			else if constexpr (std::is_same<T, u32>::value) return TypeCategory::Unsigned32;
			else if constexpr (std::is_same<T, u64>::value) return TypeCategory::Unsigned64;
			else if constexpr (std::is_same<T, f32>::value) return TypeCategory::Float32;
			else if constexpr (std::is_same<T, f64>::value) return TypeCategory::Float64;
			else if constexpr (std::is_same<T, String>::value) return TypeCategory::String;
			else if constexpr (std::is_same<T, Path>::value) return TypeCategory::String;
			else if constexpr (std::is_enum<T>::value) return TypeCategory::Enum;
			else if constexpr (std::is_class<T>::value) return TypeCategory::Class;
			else return TypeCategory::Struct;
		}

	private:
		HashMap<u32, TypeInfo> m_typeRegistry;
		HashMap<u32, ClassInfo> m_classRegistry;
		HashMap<String, u32> m_classNameToHash;
	};
}
