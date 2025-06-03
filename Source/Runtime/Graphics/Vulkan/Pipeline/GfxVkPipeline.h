/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Pipeline/GfxPipeline.h>

#include <vulkan/vulkan.h>

namespace Flax
{
	class GfxVkPipeline : public GfxPipeline
	{
	public:
		GfxVkPipeline(const GfxGraphicsPipelineDesc& desc, GfxDevice* pDevice);
		GfxVkPipeline(const GfxComputePipelineDesc& desc, GfxDevice* pDevice);
		~GfxVkPipeline() override final;

		void* Pipeline() const override final;
		void* PipelineLayout() const override final;
		void* PipelineCache() const override final;

	private:
		VkPipeline m_pipeline;
		VkPipelineLayout m_layout;
		VkPipelineCache m_cache;
	};
}
