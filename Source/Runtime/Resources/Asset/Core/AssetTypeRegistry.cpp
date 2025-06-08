#include "AssetTypeRegistry.h"

namespace Flax
{
	static HashMap<u32, AssetTypeInfo> registryMap;

	void AssetTypeRegistry::RegisterType(const String& name, const AssetTypeInfo& info)
	{
		m_registry[info.infoId] = info;
		m_nameId[name] = info.infoId;
		m_idName[info.infoId] = name;
	}

	const AssetTypeInfo* AssetTypeRegistry::TypeInfo(const String& name)
	{
		auto id = m_nameId.find(name);
		if (id == m_nameId.end())
		{
			Log::Error(LogType::Asset, "Asset type '{}' not found.", name);
			return nullptr;
		}

		auto& map = m_registry;
		auto it = map.find(id->second);

		if (it != map.end())
			return &it->second;

		Log::Error(LogType::Asset, "Asset type '{}' not found.", name);
		return nullptr;
	}

	const AssetTypeInfo* AssetTypeRegistry::TypeInfo(u32 typeId)
	{
		auto& map = m_registry;

		auto it = map.find(typeId);
		if (it != map.end())
			return &it->second;

		Log::Error(LogType::Asset, "Asset type with ID '{}' not found.", typeId);
		return nullptr;
	}
}
