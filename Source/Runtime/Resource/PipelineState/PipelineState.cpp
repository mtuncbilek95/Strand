#include "PipelineState.h"

namespace Flax
{
	PipelineState::PipelineState(const PipelineStateProps& desc) : m_props(desc)
	{
		b8 hasCompute = desc.shaders.contains(PipelineStage::Compute);
		b8 hasGraphics = false;

		for (const auto& [stage, shader] : desc.shaders)
		{
			if(stage != PipelineStage::Compute)
			{
				hasGraphics = true;
				break;
			}
		}

		if(hasCompute && hasGraphics)
		{
			Log::Critical(LogType::Resource, "PipelineStateObject cannot have both compute and graphics shaders at the same time!");
			return;
		}
	}

	PipelineState::~PipelineState()
	{
	}
}
