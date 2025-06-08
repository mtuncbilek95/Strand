#include "IResource.h"

namespace Flax
{
	IResource::IResource()
	{
		m_uuid = UuidHelper::GenerateID();
	}
}
