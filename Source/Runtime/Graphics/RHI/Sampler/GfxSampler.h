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
#include <Runtime/Graphics/RHI/Sampler/GfxSamplerDesc.h>

namespace Flax
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