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
#include <Runtime/Graphics/RHI/Sync/GfxSemaphoreDesc.h>

namespace Flax
{
	class GfxSemaphore : public GfxObject
	{
	public:
		GfxSemaphore(const GfxSemaphoreDesc& desc, GfxDevice* pDevice);
		virtual ~GfxSemaphore() override = default;

		virtual void* Semaphore() const = 0;
		virtual void WaitIdle() const = 0;
		virtual void Reset() const = 0;

	private:
		GfxSemaphoreDesc m_desc;
	};
}
