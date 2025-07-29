#include "TestResource.h"

namespace Flax
{
	TestResource::TestResource()
	{
	}

	TestResource::~TestResource()
	{
	}

	BEGIN_REFLECT_CLASS(ResourceTwo);
	REFLECT_INHERITANCE(ResourceTwo, ResourceOne);
	REFLECT_FIELD(ResourceTwo, m_twoU64);
	END_REFLECT_CLASS(ResourceTwo);

	BEGIN_REFLECT_CLASS(TestResource);
	REFLECT_INHERITANCE(TestResource, ResourceBase);
	REFLECT_FIELD(TestResource, m_newFuckery);
	END_REFLECT_CLASS(TestResource);

	BEGIN_REFLECT_CLASS(ResourceOne);
	REFLECT_INHERITANCE(ResourceOne, TestResource);
	REFLECT_FIELD(ResourceOne, m_oneU64);
	END_REFLECT_CLASS(ResourceOne);

	BEGIN_REFLECT_CLASS(ResourceThree);
	REFLECT_INHERITANCE(ResourceThree, ResourceBase);
	REFLECT_FIELD(ResourceThree, m_threeU64);
	END_REFLECT_CLASS(ResourceThree);
}
