/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>

namespace Flax
{
	class AssetTypeId : public Singleton<AssetTypeId>
	{
	public:
		u32 TypeId(const String& name);
		const String& TypeName(u32 typeId);

	private:
		HashMap<u32, String> m_idName;
		HashMap<String, u32> m_nameId;
		SharedMutex m_mutex;
	};
}
