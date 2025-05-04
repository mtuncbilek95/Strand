#include "IObject.h"

namespace Flax
{
	IObject::IObject()
	{
		m_uuid = UuidHelper::GenerateID();
	}
}
