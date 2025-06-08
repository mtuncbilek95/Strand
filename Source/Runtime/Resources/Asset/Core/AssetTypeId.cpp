#include "AssetTypeId.h"

namespace Flax
{
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
			SharedLock readLock(m_mutex);
			auto it = m_nameId.find(name);
			if (it != m_nameId.end())
				return it->second;
		}

		u32 hash = Fnv1aHash(name.data());

		{
			UniqueLock writeLock(m_mutex);

			auto& nameField = m_idName[hash];
			if (!nameField.empty() && nameField != name)
			{
				Log::Critical(LogType::Asset, "There is a hash collision for type: {}", name);
				throw std::exception("Conflict in AssetTypeId::TypeId");
			}

			m_nameId.emplace(name, hash);
			nameField = name;

			return hash;
		}
	}

	const String& AssetTypeId::TypeName(u32 typeId)
	{
		static const String unknown = "unknown";

		SharedLock lock(m_mutex);

		auto it = m_idName.find(typeId);
		return it != m_idName.end() ? it->second : unknown;
	}
}
