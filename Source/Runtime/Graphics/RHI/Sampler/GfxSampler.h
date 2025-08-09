/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Object/GfxObject.h>
#include <Runtime/Graphics/RHI/Sampler/GfxSamplerDesc.h>

namespace Strand
{
	class GfxSampler : public GfxObject
	{
	public:
		GfxSampler(const GfxSamplerDesc& desc, GfxDevice* pDevice);
		virtual ~GfxSampler() override = default;

		virtual void* Sampler() const = 0;

	private:
		GfxSamplerDesc m_desc;
	};
}