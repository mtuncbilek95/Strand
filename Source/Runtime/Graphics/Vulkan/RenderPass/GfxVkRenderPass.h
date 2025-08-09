/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/RenderPass/GfxRenderPass.h>

#include <vulkan/vulkan.h>

namespace Strand
{
	class GfxVkRenderPass final : public GfxRenderPass
	{
	public:
		GfxVkRenderPass(const GfxRenderPassDesc& desc, GfxDevice* pDevice);
		~GfxVkRenderPass() override final;

		void* Pass() const override final;

	private:
		VkRenderPass m_pass;
	};
}
