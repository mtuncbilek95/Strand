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
#include <Runtime/Graphics/RHI/Descriptor/GfxDescriptorSetDesc.h>

namespace Flax
{
	/**
	 * @class GfxDescriptorSet
	 * @brief General purpose descriptor set structure send shader unit
	 * into the shaders as textures, uniforms(cbuffer), storage or samplers
	 * etc.
	 */
	class GfxDescriptorSet : public GfxObject
	{
	public:
		GfxDescriptorSet(const GfxDescriptorSetDesc& desc, GfxDevice* pDevice);
		virtual ~GfxDescriptorSet() override = default;

		virtual void* DescSet() const = 0;
		virtual void Update(const GfxSetUpdateDesc& update) const = 0;
		
	protected:
		GfxDescriptorLayout* UsedLayout() const { return m_desc.layout; }
		GfxDescriptorPool* UsedPool() const { return m_desc.pool; }

	private:
		GfxDescriptorSetDesc m_desc;
	};
}
