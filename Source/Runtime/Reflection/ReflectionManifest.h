/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Reflection/ReflectionInfo.h>

namespace Flax
{
	class ReflectionManifest : public Singleton<ReflectionManifest>
	{
	public:
		void RegisterDependency(const ClassInfo& classInfo)
		{
			m_manifestOrder[classInfo.className] = std::move(classInfo);
		}

		void Manifest();

	private:
		HashMap<String, ClassInfo> m_manifestOrder;
		Vector<Pair<String, ClassInfo>> m_pending;
	};
}
