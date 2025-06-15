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
	typedef void* GfxHandle;

	class GfxDevice;

	class GfxObject
	{
	public:
		GfxObject(GfxDevice* pDevice) : m_owner(pDevice) {}
		virtual ~GfxObject() = default;

		GfxDevice* Root() const { return m_owner; }

	private:
		GfxDevice* m_owner;
	};
}
