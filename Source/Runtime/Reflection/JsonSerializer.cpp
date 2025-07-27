#include "JsonSerializer.h"

#include <Runtime/Reflection/JsonTypeUtils.h>

namespace Flax
{

	void JsonSerializer::SerializeImpl(const void* obj, const String& objName, OrderedJson& jsonOut)
	{
		auto classInfo = ReflectionRegistry::GetClass(objName);
		if (!classInfo)
		{
			jsonOut = OrderedJson::object();
			return;
		}

		jsonOut = OrderedJson::object();
		jsonOut["objectType"] = objName;

		for (const auto& [fieldName, fieldInfo] : classInfo->fields)
		{
			auto value = fieldInfo.getter(const_cast<void*>(obj));
			auto jsonValue = JsonTypeUtils::ToJson(value, fieldInfo.typeName);

			if (!jsonValue.is_null())
				jsonOut[fieldName] = jsonValue;
		}
	}

	void JsonSerializer::DeserializeImpl(const OrderedJson& jsonIn, void* obj, const String& objName)
	{
		if (!jsonIn.is_object())
			return;

		auto classInfo = ReflectionRegistry::GetClass(objName);
		if (!classInfo)
			return;

		if (jsonIn.contains("objectType"))
		{
			String jsonType = jsonIn["objectType"].get<String>();
			if (jsonType != objName)
			{
				Log::Critical(LogType::Reflection, "Mismatching type between 'requested: {}' & 'json: {}'", objName, jsonType);
				return;
			}
		}

		for (const auto& [fieldName, fieldInfo] : classInfo->fields)
		{
			if (!jsonIn.contains(fieldName))
				return;

			try
			{
				auto& jsonValue = jsonIn[fieldName];
				auto anyValue = JsonTypeUtils::ToAny(jsonValue, fieldInfo.typeName);

				if (anyValue.has_value())
					fieldInfo.setter(obj, anyValue);
				else
				{
					Log::Critical(LogType::Reflection, "Failed to convert field '{}' from JSON", fieldName);
					return;
				}
			}
			catch (const std::exception& e)
			{
				Log::Critical(LogType::Reflection, "Deserialize -- '{}'", e.what());
			}
		}
	}
}
