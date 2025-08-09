/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Object/GfxObject.h>
#include <Runtime/Graphics/RHI/Sync/GfxSemaphore.h>

#include <vulkan/vulkan.h>

namespace Strand
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
