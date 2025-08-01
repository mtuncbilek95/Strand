#include <Runtime/TestClass.h>

#include <Runtime/Reflection/TypeAccessor.h>

namespace Flax
{
	template<>
	class TypeAccessor<TestClass>
	{
	public:
		TypeAccessor()
		{
		}
	};

	static TypeAccessor<TestClass> tttt;
}