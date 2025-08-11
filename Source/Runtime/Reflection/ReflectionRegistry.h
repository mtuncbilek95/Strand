/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
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

namespace Strand
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
			m_classNameToHash[classInfo.className] = classInfo.classHash;

			Log::Info(LogType::Reflection, "Registered class '{}'.", classInfo.className);
		}

		template<typename T, typename... Args>
		void RegisterConstructor()
		{
			u32 classHash = typeid(T).hash_code();
			ClassInfo& classInfo = m_classRegistry[classHash];

			ConstructorInfo ctorInfo = {};
			ctorInfo.parameterTypes = GetTypeInfos<Args...>(std::index_sequence_for<Args...>{});
			ctorInfo.parameterHash = GenerateParameterHash<Args...>();
			if constexpr (sizeof...(Args) == 0) {
				ctorInfo.constructorPtr = [](const void* const*) -> void* {
					return new T();
					};
			}
			else {
				ctorInfo.constructorPtr = [&](const void* const* args) -> void* {
					return GenerateConstructFunc<T, Args...>(args, std::index_sequence_for<Args...>{});
					};
			}

			usize index = classInfo.constructors.size();
			classInfo.constructors.push_back(ctorInfo);
			classInfo.constructorLookup[ctorInfo.parameterHash] = index;
		}

		template<typename T>
		void RegisterInheritanceInfo()
		{
			u32 classHash = typeid(T).hash_code();
			ClassInfo& classInfo = m_classRegistry[classHash];
		}

		template<typename T, typename... Args>
		void RegisterMethodInfo()
		{
			u32 classHash = typeid(T).hash_code();
			ClassInfo& classInfo = m_classRegistry[classHash];
		}

		template<typename T>
		void RegisterFieldInfo(const String& fieldName, usize offset, const TypeInfo& typeInfo)
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

		ClassInfo* GetClassInfo(const String& className)
		{
			auto it = m_classNameToHash.find(className);
			if (it == m_classNameToHash.end())
			{
				Log::Critical(LogType::Reflection, "Class '{}' is not registered in the reflection system.", className);
				return nullptr;
			}
			auto classIt = m_classRegistry.find(it->second);
			if (classIt == m_classRegistry.end())
			{
				Log::Critical(LogType::Reflection, "Class '{}' is not found in the registry.", className);
				return nullptr;
			}
			return &classIt->second;
		}

		template<typename T>
		TypeInfo* GetTypeInfo()
		{
			auto it = m_typeRegistry.find(typeid(T).hash_code());
			if (it == m_typeRegistry.end())
				RegisterTypeInfo<T>();

			it = m_typeRegistry.find(typeid(T).hash_code());
			if (it == m_typeRegistry.end())
			{
				Log::Critical(LogType::Reflection, "Something unexpected is happening in the reflection system for type '{}' when getting.", typeid(T).name());
				return nullptr;
			}

			return &it->second;
		}

		template<typename T>
		FieldInfo* GetFieldInfo(const String& fieldName)
		{
			auto classIt = m_classRegistry.find(typeid(T).hash_code());
			if (classIt == m_classRegistry.end())
			{
				Log::Critical(LogType::Reflection, "Class '{}' is not registered in the reflection system.", typeid(T).name());
				return nullptr;
			}

			auto fieldIt = classIt->second.fields.find(fieldName);
			if (fieldIt == classIt->second.fields.end())
			{
				Log::Critical(LogType::Reflection, "Field '{}' is not found in class '{}'.", fieldName, typeid(T).name());
				return nullptr;
			}

			return &fieldIt->second;
		}

	private:
		template<typename T, typename... Args, usize... Is>
		void* GenerateConstructFunc(const void* const* args, std::index_sequence<Is...>)
		{
			return new T(*static_cast<const std::remove_reference_t<Args>*>(args[Is])...);
		}

		template<typename... Args>
		u32 GenerateParameterHash()
		{
			u32 hash = 0;
			((hash ^= Hash<std::type_index>{}(TypeIndex(typeid(Args))) + 0x9e3779b9 + (hash << 6) + (hash >> 2)), ...);
			return hash;
		}

		template<typename... Args, usize... Is>
		Vector<TypeInfo> GetTypeInfos(std::index_sequence<Is...>)
		{
			Vector<TypeInfo> result;
			result.reserve(sizeof...(Args));

			auto processType = [this, &result](auto index)
				{
					using Type = std::tuple_element_t<index, std::tuple<Args...>>;
					result.push_back(*GetTypeInfo<Type>());
				};

			(processType(std::integral_constant<usize, Is>{}), ...);
			return result;
		}

		template<typename T>
		TypeCategory FindCategory()
		{
			if constexpr (std::is_same<RemoveCVRef<T>, RemoveCVRef<b8>>::value) return TypeCategory::Boolean;
			else if constexpr (std::is_same<RemoveCVRef<T>, RemoveCVRef<c8>>::value) return TypeCategory::Char;
			else if constexpr (std::is_same<RemoveCVRef<T>, RemoveCVRef<i8>>::value) return TypeCategory::Signed8;
			else if constexpr (std::is_same<RemoveCVRef<T>, RemoveCVRef<i16>>::value) return TypeCategory::Signed16;
			else if constexpr (std::is_same<RemoveCVRef<T>, RemoveCVRef<i32>>::value) return TypeCategory::Signed32;
			else if constexpr (std::is_same<RemoveCVRef<T>, RemoveCVRef<i64>>::value) return TypeCategory::Signed64;
			else if constexpr (std::is_same<RemoveCVRef<T>, RemoveCVRef<u8>>::value) return TypeCategory::Unsigned8;
			else if constexpr (std::is_same<RemoveCVRef<T>, RemoveCVRef<u16>>::value) return TypeCategory::Unsigned16;
			else if constexpr (std::is_same<RemoveCVRef<T>, RemoveCVRef<u32>>::value) return TypeCategory::Unsigned32;
			else if constexpr (std::is_same<RemoveCVRef<T>, RemoveCVRef<u64>>::value) return TypeCategory::Unsigned64;
			else if constexpr (std::is_same<RemoveCVRef<T>, RemoveCVRef<f32>>::value) return TypeCategory::Float32;
			else if constexpr (std::is_same<RemoveCVRef<T>, RemoveCVRef<f64>>::value) return TypeCategory::Float64;
			else if constexpr (std::is_same<RemoveCVRef<T>, RemoveCVRef<String>>::value) return TypeCategory::String;
			else if constexpr (std::is_same<RemoveCVRef<T>, RemoveCVRef<Path>>::value) return TypeCategory::String;
			else if constexpr (std::is_enum<RemoveCVRef<T>>::value) return TypeCategory::Enum;
			else if constexpr (std::is_class<RemoveCVRef<T>>::value) return TypeCategory::Class;
			else return TypeCategory::Struct;
		}

	private:
		HashMap<u32, TypeInfo> m_typeRegistry;
		HashMap<u32, ClassInfo> m_classRegistry;
		HashMap<String, u32> m_classNameToHash;
	};
}
