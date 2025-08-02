#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Reflection/TypeAccessor.h>
#include <Runtime/Reflection/Reflection.h>

namespace Strand
{
	class TestClass
	{
		FLAX_OBJECT(TestClass)
	public:
		TestClass()
		{
			m_testVal = 25;
		}

	private:
		u64 m_testVal;
	};
}