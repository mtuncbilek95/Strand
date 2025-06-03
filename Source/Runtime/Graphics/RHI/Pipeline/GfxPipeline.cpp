#include "GfxPipeline.h"

namespace Flax
{
	GfxPipeline::GfxPipeline(const GfxGraphicsPipelineDesc& desc, GfxDevice* pDevice) : GfxObject(pDevice),
		m_gDesc(desc), m_type(PipelineType::Graphics)
	{
	}

	GfxPipeline::GfxPipeline(const GfxComputePipelineDesc& desc, GfxDevice* pDevice) : GfxObject(pDevice),
		m_cDesc(desc), m_type(PipelineType::Compute)
	{
	}
}