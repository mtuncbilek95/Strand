#include "TestResource.h"

namespace Flax
{
	TestResource::TestResource()
	{
	}

	TestResource::~TestResource()
	{
	}

	BEGIN_REFLECT_CLASS(TestResource);
	REFLECT_INHERITANCE(TestResource, ResourceBase);
	REFLECT_FIELD(TestResource, m_newFuckery);
	END_REFLECT_CLASS(TestResource);
}
