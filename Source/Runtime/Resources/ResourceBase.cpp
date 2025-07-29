#include "ResourceBase.h"

namespace Flax
{
	ResourceBase::ResourceBase()
	{
	}

	ResourceBase::~ResourceBase()
	{
	}

	BEGIN_REFLECT_CLASS(ResourceBase);
	REFLECT_FIELD(ResourceBase, m_test);
	END_REFLECT_CLASS(ResourceBase);
}
