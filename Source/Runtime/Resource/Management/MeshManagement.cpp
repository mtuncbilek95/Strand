#include "MeshManagement.h"

namespace Flax
{
	MeshManagement::MeshManagement()
	{
	}

	MeshManagement::~MeshManagement()
	{
		m_meshes.clear();
		m_materials.clear();
	}
}