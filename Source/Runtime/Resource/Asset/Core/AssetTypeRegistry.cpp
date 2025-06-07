#include "AssetTypeRegistry.h"

namespace Flax
{
	static HashMap<u32, AssetTypeInfo> registryMap;
	static HashMap<String, u32> idStores;
	static HashMap<u32, String> nameStores;

	void AssetTypeRegistry::RegisterType(const String& name, const AssetTypeInfo& info)
	{
		registryMap[info.infoId] = info;
		idStores[name] = info.infoId;
		nameStores[info.infoId] = name;
	}

	const AssetTypeInfo* AssetTypeRegistry::TypeInfo(const String& name)
	{
		auto id = idStores.find(name);
		if (id == idStores.end())
		{
			Log::Error(LogType::Asset, "Asset type '{}' not found.", name);
			return nullptr;
		}

		auto& map = registryMap;
		auto it = map.find(id->second);

		if (it != map.end())
			return &it->second;

		Log::Error(LogType::Asset, "Asset type '{}' not found.", name);
		return nullptr;
	}

	const AssetTypeInfo* AssetTypeRegistry::TypeInfo(u32 typeId)
	{
		auto& map = registryMap;

		auto it = map.find(typeId);
		if (it != map.end())
			return &it->second;

		Log::Error(LogType::Asset, "Asset type with ID '{}' not found.", typeId);
		return nullptr;
	}
}
