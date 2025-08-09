/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Object/GfxObject.h>
#include <Runtime/Graphics/RHI/Descriptor/GfxDescriptorLayoutDesc.h>

namespace Strand
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
