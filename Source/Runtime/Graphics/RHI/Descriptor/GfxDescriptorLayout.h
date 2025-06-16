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
#include <Runtime/Graphics/RHI/Descriptor/GfxDescriptorLayoutDesc.h>

namespace Flax
{
	/**
	 * @class GfxDescriptorLayout
	 * @brief General purpose layout structure for shader inputs such 
	 * as textures, cbuffer(uniform), storage etc. It will be used in
	 * pipeline classes.
	 */
	class GfxDescriptorLayout : public GfxObject
	{
	public:
		GfxDescriptorLayout(const GfxDescriptorLayoutDesc& desc, GfxDevice* pDevice);
		virtual ~GfxDescriptorLayout() override = default;

		virtual void* DescLayout() const = 0;

	private:
		GfxDescriptorLayoutDesc m_desc;
	};
}
