#include <Runtime/Core/CoreMinimal.h>
#include <iostream>

using namespace Flax;

class ObjectBase
{
public:
	virtual ~ObjectBase() = default;
};

struct FieldInfo
{
	String fieldName;
	String typeName;
	usize typeHash;

	function<Any(void*)> getter;
	function<void(void*, const Any&)> setter;

	HashMap<String, Any> attirbutes;
};

struct ClassInfo
{
	String className;
	usize size;

	function<Ref<ObjectBase>()> constructor;

	HashMap<String, FieldInfo> fields;
	HashMap<String, Any> attributes;
};

class ReflectionRegistry
{
public:
	static void RegisterClass(const String& className, const ClassInfo& classInfo)
	{
		auto& classes = ReflectedClasses();
		if (classes.contains(className))
			Log::Warn(LogType::Engine, "Class '{}' is already registered. Overwriting existing class info.", className);

		classes[className] = classInfo;
	}

	static void RegisterField(const String& className, const String& fieldName, const FieldInfo& fieldInfo)
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
			if (typeName == typeid(i32).name())
				return std::to_string(std::any_cast<i32>(value));
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
		if (typeName == typeid(i32).name()) return sizeof(i32);
		if (typeName == typeid(f32).name()) return sizeof(f32);
		if (typeName == typeid(f64).name()) return sizeof(f64);
		if (typeName == typeid(b8).name()) return sizeof(b8);
		if (typeName == typeid(String).name()) return sizeof(String);
		return 0;
	}
};

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
            ReflectionRegistry::RegisterClass(#ClassName, std::move(classInfo)); \
        } \
    }; \
    \
    static ClassName##_ReflectionRegister ClassName##RegisterInstance; \

class TestClass : public ObjectBase
{
	FLAX_OBJECT(TestClass)
public:
	TestClass() = default;
	~TestClass() = default;

private:
	int m_test = 12;
};

BEGIN_REFLECT_CLASS(TestClass)
	REFLECT_FIELD(TestClass, m_test)
END_REFLECT_CLASS(TestClass)

int main()
{
	auto test = Reflection::CreateInstance<TestClass>();
}