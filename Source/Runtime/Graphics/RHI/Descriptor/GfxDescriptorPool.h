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
#include <Runtime/Graphics/RHI/Descriptor/GfxDescriptorPoolDesc.h>

namespace Flax
{
	class GfxDescriptorPool : public GfxObject
	{
	public:
		GfxDescriptorPool(const GfxDescriptorPoolDesc& desc, GfxDevice* pDevice);
		virtual ~GfxDescriptorPool() override = default;

		virtual void* DescPool() const = 0;

	private:
		GfxDescriptorPoolDesc m_desc;
	};
}
