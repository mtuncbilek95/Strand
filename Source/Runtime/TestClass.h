#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Reflection/TypeAccessor.h>
#include <Runtime/Reflection/Reflection.h>

namespace Strand
{
	STRAND_CLASS()
	class TestClass
	{
		STRAND_OBJECT(TestClass)
	public:
		TestClass()
		{
			m_testVal = 25;
		}

		STRAND_METHOD()
		void TestMethod(const String& param1, usize param2);

	private:
		STRAND_FIELD()
		u64 m_testVal;
	};
}