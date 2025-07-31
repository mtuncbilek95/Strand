#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Reflection/ReflectionRegistry.h>

using namespace Flax;
int main()
{
	ReflectionRegistry::Get().RegisterReflectionType<String>();
	ReflectionRegistry::Get().RegisterReflectionType<i8>();
	ReflectionRegistry::Get().RegisterReflectionType<i16>();
	ReflectionRegistry::Get().RegisterReflectionType<i32>();
}