/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Object/GfxObject.h>
#include <Runtime/Graphics/RHI/Sync/GfxFenceDesc.h>

namespace Flax
{
	class GfxFence : public GfxObject
	{
	public:
		GfxFence(const GfxFenceDesc& desc, GfxDevice* pDevice);
		virtual ~GfxFence() override = default;

		virtual void* Fence() const = 0;
		virtual void WaitIdle() const = 0;
		virtual void Reset() const = 0;

	private:
		GfxFenceDesc m_desc;
	};
}
