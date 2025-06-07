#include "AssetTypeId.h"

namespace Flax
{
	static HashMap<u32, String> storedNames;
	static HashMap<String, u32> storedIds;
	static SharedMutex registryMutex;

	static constexpr u32 Fnv1aHash(const char* str)
	{
		u32 hash = 2166136261u;
		while (*str)
		{
			hash ^= static_cast<u32>(*str++);
			hash *= 16777619u; 
		}
		return hash;
	}

	u32 AssetTypeId::TypeId(const String& name)
	{
		{
			SharedLock readLock(registryMutex);
			auto it = storedIds.find(name);
			if (it != storedIds.end())
				return it->second;
		}

		u32 hash = Fnv1aHash(name.data());

		{
			UniqueLock writeLock(registryMutex);

			auto& nameField = storedNames[hash];
			if (!nameField.empty() && nameField != name)
			{
				Log::Critical(LogType::Asset, "There is a hash collision for type: {}", name);
				throw std::exception("Conflict in AssetTypeId::TypeId");
			}

			storedIds.emplace(name, hash);
			nameField = name;

			return hash;
		}
	}

	const String& AssetTypeId::TypeName(u32 typeId)
	{
		static const String unknown = "unknown";

		SharedLock lock(registryMutex);

		auto it = storedNames.find(typeId);
		return it != storedNames.end() ? it->second : unknown;
	}
}
