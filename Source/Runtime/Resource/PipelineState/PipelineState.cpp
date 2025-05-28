#include "PipelineState.h"

namespace Flax
{
	PipelineState::PipelineState(const PipelineStateProps& desc)
	{
		b8 hasCompute = desc.shaders.contains(PipelineStage::Compute);
		b8 hasGraphics = false;

		for (const auto& [stage, shader] : desc.shaders)
		{
			if (stage != PipelineStage::Compute)
			{
				hasGraphics = true;
				break;
			}
		}

		if (hasCompute && hasGraphics)
		{
			Log::Critical(LogType::Resource, "PipelineStateObject cannot have both compute and graphics shaders at the same time!");
			return;
		}
	}

	PipelineState::~PipelineState()
	{
	}

	Ref<IResource> CreatePipelineState(const Any& args)
	{
		const auto& props = std::any_cast<const PipelineStateProps&>(args);
		return NewRef<PipelineState>(props);
	}

	struct PipelineStateRegister
	{
		PipelineStateRegister() { GlobalResourceResolver::RegisterResource("PipelineState", CreatePipelineState); }
	};

	static PipelineStateRegister gbPipelineStateRegistry;
}
