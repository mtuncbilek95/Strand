#include "NameTagComponent.h"

namespace Strand
{
	NameTagComponent::NameTagComponent(const String& entityName)
		: m_entityName(entityName)
	{
		m_componentName = NameTagComponent::StaticClassName();
	}
}