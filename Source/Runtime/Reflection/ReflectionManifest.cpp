#include "ReflectionManifest.h"

#include <Runtime/Reflection/ReflectionRegistry.h>

namespace Flax
{
	void ReflectionManifest::Manifest()
	{
		m_pending.reserve(m_manifestOrder.size());

		for (auto& [className, info] : m_manifestOrder)
		{
			if (info.superClass.empty())
				ReflectionRegistry::DefineClass(info.className, std::move(info));
			else
				m_pending.push_back({ std::move(info.superClass), std::move(info) });
		}

		while (!m_pending.empty())
		{
			Vector<decltype(m_pending)::iterator> toRemove;
			toRemove.reserve(m_pending.size());

			for (auto it = m_pending.begin(); it != m_pending.end(); ++it)
			{
				if (ReflectionRegistry::HasClass(it->first))
				{
					auto& info = it->second;
					info.inheritances = ReflectionRegistry::GetInheritances(it->first);
					ReflectionRegistry::DefineClass(info.className, std::move(info));
					toRemove.push_back(it);
				}
			}

			for (auto rit = toRemove.rbegin(); rit != toRemove.rend(); ++rit)
				m_pending.erase(*rit);

			if (toRemove.empty())
				break;
		}

		m_manifestOrder.clear();
		m_pending.clear();
	}
}
