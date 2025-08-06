#include "ReflectionRegistry.h"

namespace Strand
{
	struct GeneralPrimitiveRegister
	{
		GeneralPrimitiveRegister()
		{
			ReflectionRegistry::Get().RegisterTypeInfo<i8>();
			ReflectionRegistry::Get().RegisterTypeInfo<i16>();
			ReflectionRegistry::Get().RegisterTypeInfo<i32>();
			ReflectionRegistry::Get().RegisterTypeInfo<i64>();
			ReflectionRegistry::Get().RegisterTypeInfo<u8>();
			ReflectionRegistry::Get().RegisterTypeInfo<u16>();
			ReflectionRegistry::Get().RegisterTypeInfo<u32>();
			ReflectionRegistry::Get().RegisterTypeInfo<u64>();
			ReflectionRegistry::Get().RegisterTypeInfo<c8>();
			ReflectionRegistry::Get().RegisterTypeInfo<b8>();
			ReflectionRegistry::Get().RegisterTypeInfo<String>();
			ReflectionRegistry::Get().RegisterTypeInfo<Path>();
		}
	};
	static GeneralPrimitiveRegister gbGeneralPrimitiveRegister;
}