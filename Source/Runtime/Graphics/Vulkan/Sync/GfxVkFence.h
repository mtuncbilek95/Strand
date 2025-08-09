/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Object/GfxObject.h>
#include <Runtime/Graphics/RHI/Sync/GfxFence.h>

#include <vulkan/vulkan.h>

namespace Strand
{
	class GfxVkFence : public GfxFence
	{
	public:
		GfxVkFence(const GfxFenceDesc& desc, GfxDevice* pDevice);
		~GfxVkFence() override final;

		void* Fence() const override final;
		void WaitIdle() const override final;
		void Reset() const override final;

	private:
		VkFence m_fence;
	};
}
