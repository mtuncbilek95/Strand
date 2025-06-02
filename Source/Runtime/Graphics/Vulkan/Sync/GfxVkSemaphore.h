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
#include <Runtime/Graphics/RHI/Sync/GfxSemaphore.h>

#include <vulkan/vulkan.h>

namespace Flax
{
	class GfxVkSemaphore final : public GfxSemaphore
	{
	public:
		GfxVkSemaphore(const GfxSemaphoreDesc& desc, GfxDevice* pDevice);
		~GfxVkSemaphore() override final;

		void* Semaphore() const override final;
		void WaitIdle() const override final;
		void Reset() const override final;
		
	private:
		VkSemaphore m_semaphore;
	};
}
