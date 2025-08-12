#include "TransformComponent.h"

namespace Strand
{
	TransformComponent::TransformComponent() : m_position(Math::Vec3f()), 
		m_rotation(Math::Vec3f()), m_scale(Math::Vec3f())
	{
		m_componentName = TransformComponent::StaticClassName();
	}
}