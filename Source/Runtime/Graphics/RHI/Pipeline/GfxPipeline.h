/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Object/GfxObject.h>
#include <Runtime/Graphics/RHI/Pipeline/GfxPipelineDesc.h>

namespace Strand
{
	class GfxPipeline : public GfxObject
	{
	public:
		GfxPipeline(const GfxGraphicsPipelineDesc& desc, GfxDevice* pDevice);
		GfxPipeline(const GfxComputePipelineDesc& desc, GfxDevice* pDevice);
		virtual ~GfxPipeline() override = default;

		virtual void* Pipeline() const = 0;
		virtual void* PipelineLayout() const = 0;
		virtual void* PipelineCache() const = 0;

		PipelineType Type() const { return m_type; }

	private:
		GfxGraphicsPipelineDesc m_gDesc;
		GfxComputePipelineDesc m_cDesc;

		PipelineType m_type;
	};
}
