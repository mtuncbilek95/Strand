/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Reflection/ReflectionInfo.h>

namespace Flax
{
	class ReflectionRegistry
	{
	public:
		static void DefineClass(const String& className, const ClassInfo& classInfo)
		{
			auto& classes = ReflectedClasses();
			if (classes.contains(className))
				Log::Warn(LogType::Engine, "Class '{}' is already registered. Overwriting existing class info.", className);

			classes[className] = classInfo;
		}

		static void UndefineClass(const String& className, const String& fieldName, const FieldInfo& fieldInfo)
		{
			auto& classes = ReflectedClasses();
			if (!classes.contains(className))
			{
				Log::Error(LogType::Engine, "Class '{}' is not registered. Cannot register field '{}'.", className, fieldName);
				return;
			}

			auto& classInfo = classes[className];
			if (classInfo.fields.contains(fieldName))
				Log::Warn(LogType::Engine, "Field '{}' in class '{}' is already registered. Overwriting existing field info.", fieldName, className);
			classInfo.fields[fieldName] = fieldInfo;
		}

		static b8 HasClass(const String& className)
		{
			return ReflectedClasses().contains(className);
		}

		static const ClassInfo* GetClass(const String& className)
		{
			auto& classes = ReflectedClasses();

			auto it = classes.find(className);
			if (it == classes.end()) [[unlikely]]
			{
				Log::Error(LogType::Engine, "Class '{}' is not registered.", className);
				return nullptr;
			}

			return &it->second;
		}

		static const FieldInfo* GetField(const String& className, const String& fieldName)
		{
			auto classInfo = GetClass(className);
			if (!classInfo)
				return nullptr;

			auto it = classInfo->fields.find(fieldName);
			if (it == classInfo->fields.end()) [[unlikely]]
			{
				Log::Error(LogType::Engine, "Field '{}' in class '{}' is not registered.", fieldName, className);
				return nullptr;
			}
			return &it->second;
		}

		static Vector<String> GetAllClassNames()
		{
			Vector<String> returnVec;

			for (const auto& [className, _] : ReflectedClasses())
				returnVec.emplace_back(className);

			return returnVec;
		}

	private:
		static HashMap<String, ClassInfo>& ReflectedClasses()
		{
			static HashMap<String, ClassInfo> classes;
			return classes;
		}
	};

	struct ReflectionUtils
	{
		static String AnyToString(const Any& value, const String& typeName)
		{
			try
			{
				if (typeName == typeid(i8).name())
					return std::to_string(std::any_cast<i8>(value));
				else if(typeName == typeid(i16).name())
					return std::to_string(std::any_cast<i16>(value));
				else if (typeName == typeid(i32).name())
					return std::to_string(std::any_cast<i32>(value));
				else if (typeName == typeid(i64).name())
					return std::to_string(std::any_cast<i64>(value));
				else if (typeName == typeid(u8).name())
					return std::to_string(std::any_cast<u8>(value));
				else if (typeName == typeid(u16).name())
					return std::to_string(std::any_cast<u16>(value));
				else if (typeName == typeid(u32).name())
					return std::to_string(std::any_cast<u32>(value));
				else if (typeName == typeid(u64).name())
					return std::to_string(std::any_cast<u64>(value));
				else if (typeName == typeid(f32).name())
					return std::to_string(std::any_cast<f32>(value));
				else if (typeName == typeid(f64).name())
					return std::to_string(std::any_cast<f64>(value));
				else if (typeName == typeid(b8).name())
					return std::any_cast<b8>(value) ? "true" : "false";
				else if (typeName == typeid(String).name())
					return std::any_cast<String>(value);

				return "<unknown_type>";
			}
			catch (const std::bad_any_cast& e)
			{
				return "<bad_cast>";
			}
		}

		static Any StringToAny(const String& str, const String& typeName)
		{
			if (typeName == typeid(i32).name())
				return std::stoi(str);
			else if (typeName == typeid(f32).name())
				return std::stof(str);
			else if (typeName == typeid(f64).name())
				return std::stod(str);
			else if (typeName == typeid(b8).name())
				return str == "true" || str == "1";
			else if (typeName == typeid(String).name())
				return str;
			return Any();
		}

		static usize GetTypeSize(const String& typeName)
		{
			if (typeName == typeid(i8).name()) return sizeof(i8);
			if (typeName == typeid(i16).name()) return sizeof(i16);
			if (typeName == typeid(i32).name()) return sizeof(i32);
			if (typeName == typeid(i64).name()) return sizeof(i64);
			if (typeName == typeid(u8).name()) return sizeof(u8);
			if (typeName == typeid(u16).name()) return sizeof(u16);
			if (typeName == typeid(u32).name()) return sizeof(u32);
			if (typeName == typeid(u64).name()) return sizeof(u64);
			if (typeName == typeid(f32).name()) return sizeof(f32);
			if (typeName == typeid(f64).name()) return sizeof(f64);
			if (typeName == typeid(b8).name()) return sizeof(b8);
			if (typeName == typeid(String).name()) return sizeof(String);
			return 0;
		}
	};
}
