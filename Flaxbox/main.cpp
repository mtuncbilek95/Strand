#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Reflection/Reflection.h>
#include <Runtime/Reflection/JsonSerializer.h>

#include <iostream>

namespace Flax
{
	class TestClass : public ObjectBase
	{
		FLAX_OBJECT(TestClass)
	public:
		TestClass() = default;
		~TestClass() = default;

	private:
		u32 m_test = 12;
		String m_val = "Testing the class";
		Math::Vec3f m_vec = { 1.0f, 2.f, 3.f };
	};

	BEGIN_REFLECT_CLASS(TestClass)
		REFLECT_FIELD(TestClass, m_test)
		REFLECT_FIELD(TestClass, m_val)
		REFLECT_FIELD(TestClass, m_vec)
	END_REFLECT_CLASS(TestClass)
}

using namespace Flax;

int main()
{
	auto test = Reflection::CreateInstance<TestClass>();
	OrderedJson jsonFile;
	JsonSerializer::Serialize(*test.get(), jsonFile);

	std::cout << "Serialize 1\n" << jsonFile.dump(4) << std::endl;

	jsonFile["m_test"] = 26;
	jsonFile["m_val"] = "Deserialize this bitch";
	jsonFile["m_vec"]["x"] = 5.f;
	jsonFile["m_vec"]["y"] = 8.f;
	jsonFile["m_vec"]["z"] = 9.f;
	
	auto anotherShit = Reflection::CreateInstance<TestClass>();
	JsonSerializer::Deserialize(jsonFile, *anotherShit.get());

	OrderedJson justADump;
	JsonSerializer::Serialize(*anotherShit.get(), justADump);

	std::cout << "Serialize 2\n" << justADump.dump(4) << std::endl;
}