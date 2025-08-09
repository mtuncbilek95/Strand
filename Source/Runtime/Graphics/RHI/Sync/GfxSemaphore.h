/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Object/GfxObject.h>
#include <Runtime/Graphics/RHI/Sync/GfxSemaphoreDesc.h>

namespace Strand
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
