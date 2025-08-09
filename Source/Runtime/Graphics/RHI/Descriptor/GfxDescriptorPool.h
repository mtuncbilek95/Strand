/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Object/GfxObject.h>
#include <Runtime/Graphics/RHI/Descriptor/GfxDescriptorPoolDesc.h>

namespace Strand
{
	/**
	 * @class GfxDescriptorPool
	 * @brief General purpose descriptor pool structure to pool all the shader
	 * units that will be defined.
	 */
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
