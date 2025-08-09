/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>

namespace Strand
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
