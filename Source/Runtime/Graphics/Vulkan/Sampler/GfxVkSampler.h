/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Sampler/GfxSampler.h>

#include <vulkan/vulkan.h>

namespace Flax
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