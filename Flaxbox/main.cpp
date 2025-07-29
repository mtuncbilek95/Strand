#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Reflection/Reflection.h>
#include <Runtime/Reflection/JsonSerializer.h>
#include <Runtime/Resources/TestResource.h>
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

	BEGIN_REFLECT_CLASS(TestClass);
	REFLECT_FIELD(TestClass, m_test);
	REFLECT_FIELD(TestClass, m_val);
	REFLECT_FIELD(TestClass, m_vec);
	END_REFLECT_CLASS(TestClass);

	class InheritClass : public TestClass
	{
		FLAX_OBJECT(InheritClass)
	public:
		InheritClass() = default;
		~InheritClass() = default;

	private:
		u64 m_inheritTest = 28;
	};

	BEGIN_REFLECT_CLASS(InheritClass);
	REFLECT_INHERITANCE(InheritClass, TestClass);
	REFLECT_FIELD(InheritClass, m_inheritTest);
	END_REFLECT_CLASS(InheritClass);

	class GrandClass : public InheritClass
	{
		FLAX_OBJECT(GrandClass)
	public:
		GrandClass() = default;
		~GrandClass() = default;

	private:
		String m_grandString = "GrandClass > InheritClass > TestClass";
	};

	BEGIN_REFLECT_CLASS(GrandClass);
	REFLECT_INHERITANCE(GrandClass, InheritClass);
	REFLECT_FIELD(GrandClass, m_grandString);
	END_REFLECT_CLASS(GrandClass);
}

using namespace Flax;

int main()
{
	auto start = std::chrono::high_resolution_clock::now();
	ReflectionManifest::Get().Manifest();
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	std::cout << "ReflectionManifest::InitializeReflection() took: "
		<< duration.count() << " microseconds ("
		<< duration.count() / 1000.0 << " ms)" << std::endl;

	auto test = Reflection::CreateInstance<GrandClass>();
	OrderedJson jsonFile;
	JsonSerializer::Serialize(*test.get(), jsonFile);

	std::cout << "Serialize 1\n" << jsonFile.dump(4) << std::endl;

	//jsonFile["m_test"] = 26;
	//jsonFile["m_val"] = "Deserialize this bitch";
	//jsonFile["m_vec"]["x"] = 5.f;
	//jsonFile["m_vec"]["y"] = 8.f;
	//jsonFile["m_vec"]["z"] = 9.f;
	//
	//auto anotherShit = Reflection::CreateInstance<TestClass>();
	//JsonSerializer::Deserialize(jsonFile, *anotherShit.get());

	//OrderedJson justADump;
	//JsonSerializer::Serialize(*anotherShit.get(), justADump);

	//std::cout << "Serialize 2\n" << justADump.dump(4) << std::endl;
}