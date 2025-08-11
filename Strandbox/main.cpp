#include <Runtime/Reflection/Reflection.h>

namespace Strand
{
	class BaseClass
	{
		virtual ~BaseClass() = default;
	};

	STRAND_CLASS()
		class TestClass
	{
		STRAND_OBJECT(TestClass)
	public:
		TestClass() = default;
		~TestClass() = default;

	private:
		STRAND_FIELD()
			i32 m_testField = 7;
	};

	template<>
	class TypeAccessor<TestClass>
	{
	public:
		TypeAccessor()
		{
			ReflectionRegistry::Get().RegisterClassInfo<TestClass>();
			ReflectionRegistry::Get().RegisterConstructor<TestClass>();
			ReflectionRegistry::Get().RegisterFieldInfo<TestClass>("testField",
				offsetof(TestClass, m_testField), *ReflectionRegistry::Get().GetTypeInfo<i32>());
		}
	};

	static TypeAccessor<TestClass> s_testClassAccessor;
}

using namespace Strand;

int main()
{
	auto* testing = new TestClass();

	auto val = ReflectionRegistry::Get().GetFieldInfo<TestClass>("testField")->GetValue<i32>(testing);
	printf("Value of testField: %d\n", *val);
	ReflectionRegistry::Get().GetFieldInfo<TestClass>("testField")->SetValue<i32>(testing, 42);

	printf("Value of testField: %d\n", *val);
}