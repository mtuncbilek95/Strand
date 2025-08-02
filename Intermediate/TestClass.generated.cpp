#include <Runtime/TestClass.h>

#include <Runtime/Reflection/TypeAccessor.h>

namespace Strand
{
	template<>
	class TypeAccessor<TestClass>
	{
	public:
		TypeAccessor()
		{
		}
	};

	static TypeAccessor<TestClass> gb_typeAccessorTestClass;
}