#include "JsonTypeUtils.h"

namespace Flax
{
	Json JsonTypeUtils::ToJson(const Any& value, const String& typeName)
	{
		try
		{
			if (typeName == typeid(i8).name())
				return std::any_cast<i8>(value);
			else if (typeName == typeid(i16).name())
				return std::any_cast<i16>(value);
			else if (typeName == typeid(i32).name())
				return std::any_cast<i32>(value);
			else if (typeName == typeid(i64).name())
				return std::any_cast<i64>(value);
			else if (typeName == typeid(u8).name())
				return std::any_cast<u8>(value);
			else if (typeName == typeid(u16).name())
				return std::any_cast<u16>(value);
			else if (typeName == typeid(u32).name())
				return std::any_cast<u32>(value);
			else if (typeName == typeid(u64).name())
				return std::any_cast<u64>(value);
			else if (typeName == typeid(f32).name())
				return std::any_cast<f32>(value);
			else if (typeName == typeid(f64).name())
				return std::any_cast<f64>(value);
			else if (typeName == typeid(String).name())
				return std::any_cast<String>(value);

			else if (typeName == typeid(Math::Vec2f).name())
			{
				auto vec = std::any_cast<Math::Vec2f>(value);
				return Json{ {"x", vec.x}, {"y", vec.y} };
			}
			else if (typeName == typeid(Math::Vec3f).name())
			{
				auto vec = std::any_cast<Math::Vec3f>(value);
				return Json{ {"x", vec.x}, {"y", vec.y}, {"z", vec.z} };
			}
			else if (typeName == typeid(Math::Vec4f).name())
			{
				auto vec = std::any_cast<Math::Vec4f>(value);
				return Json{ {"x", vec.x}, {"y", vec.y}, {"z", vec.z}, {"w", vec.w} };
			}
		}
		catch (const std::bad_any_cast& e)
		{
			Log::Critical(LogType::Reflection, "Bad-Cast '{}'", e.what());
			return Json::object();
		}

		return Json::object();
	}

	Any JsonTypeUtils::ToAny(const Json& jsonFile, const String& typeName)
	{
		try
		{
			if (typeName == typeid(i8).name())
				return jsonFile.get<i8>();
			else if (typeName == typeid(i16).name())
				return jsonFile.get<i16>();
			else if (typeName == typeid(i32).name())
				return jsonFile.get<i32>();
			else if (typeName == typeid(i64).name())
				return jsonFile.get<i64>();
			else if (typeName == typeid(u8).name())
				return jsonFile.get<u8>();
			else if (typeName == typeid(u16).name())
				return jsonFile.get<u16>();
			else if (typeName == typeid(u32).name())
				return jsonFile.get<u32>();
			else if (typeName == typeid(u64).name())
				return jsonFile.get<u64>();
			else if (typeName == typeid(f32).name())
				return jsonFile.get<f32>();
			else if (typeName == typeid(f64).name())
				return jsonFile.get<f64>();
			else if (typeName == typeid(String).name())
				return jsonFile.get<String>();

			else if (typeName == typeid(Math::Vec2f).name())
			{
				return Math::Vec2f(
					jsonFile["x"].get<f32>(),
					jsonFile["y"].get<f32>()
				);
			}
			else if (typeName == typeid(Math::Vec3f).name())
			{
				return Math::Vec3f(
					jsonFile["x"].get<f32>(),
					jsonFile["y"].get<f32>(),
					jsonFile["z"].get<f32>()
				);
			}
			else if (typeName == typeid(Math::Vec4f).name())
			{
				return Math::Vec4f(
					jsonFile["x"].get<f32>(),
					jsonFile["y"].get<f32>(),
					jsonFile["z"].get<f32>(),
					jsonFile["w"].get<f32>()
				);
			}
		}
		catch (const Json::exception& e)
		{
			Log::Critical(LogType::Reflection, "JsonException -- '{}'", e.what());
			return Any();
		}

		return Any();
	}
}
