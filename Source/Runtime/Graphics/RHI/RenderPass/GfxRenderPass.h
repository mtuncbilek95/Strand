/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Object/GfxObject.h>
#include <Runtime/Graphics/RHI/RenderPass/GfxRenderPassDesc.h>

namespace Strand
{
	class GfxRenderPass : public GfxObject
	{
	public:
		GfxRenderPass(const GfxRenderPassDesc& desc, GfxDevice* pDevice);
		virtual ~GfxRenderPass() override = default;

		virtual void* Pass() const = 0;

	private:
		GfxRenderPassDesc m_desc;
	};
}
