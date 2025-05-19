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

	Ref<MeshResource> MeshManagement::GetMeshResource(u32 hashId)
	{
		auto it = m_meshes.find(meshId);

		if (it != m_meshes.end()) [[unlikely]]
			return it->second;

		Log::Critical(LogType::Resource, "Mesh not found: {}", hashId);
		return nullptr;
	}
}