/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Sampler/GfxSampler.h>

#include <vulkan/vulkan.h>

namespace Strand
{
	class GfxVkSampler : public GfxSampler
	{
	public:
		GfxVkSampler(const GfxSamplerDesc& desc, GfxDevice* pDevice);
		~GfxVkSampler() override final;

		void* Sampler() const override final;

	private:
		VkSampler m_sampler;
	};
}