#include "MeshManagement.h"

namespace Flax
{
	MeshManagement::MeshManagement()
	{
	}

	MeshManagement::~MeshManagement()
	{
		// TODO: Add a cache system to record what you have earlier.

		m_meshes.clear();
		m_materials.clear();
	}

	Ref<MeshResource> MeshManagement::GetMeshResource(u32 hashId)
	{
		if (hashId == 0)
			return nullptr;

		auto it = m_meshes.find(hashId);

		if (it != m_meshes.end()) [[unlikely]]
			return it->second;

		Log::Critical(LogType::Resource, "Mesh not found: {}", hashId);
		return nullptr;
	}

	Ref<MaterialResource> MeshManagement::GetMaterialResource(u32 hashId)
	{
		if (hashId == 0)
			return nullptr;

		auto it = m_materials.find(hashId);

		if (it != m_materials.end()) [[unlikely]]
			return it->second;

		Log::Critical(LogType::Resource, "Mesh not found: {}", hashId);
		return nullptr;
	}
}