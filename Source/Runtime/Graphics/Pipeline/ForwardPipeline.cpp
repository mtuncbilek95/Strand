#include "ForwardPipeline.h"

#include <Runtime/ShaderCompiler/ShaderCompiler.h>

namespace Flax
{
	ForwardPipeline::ForwardPipeline(const ForwardPipelineCreateInfo& createInfo, FvkDevice* pDevice)
	{
		ReadArray<u32> vByte = ShaderCompiler::CompileShader(createInfo.vPath, "", "main");
		ReadArray<u32> fByte = ShaderCompiler::CompileShader(createInfo.fPath, "", "main");
	}

	ForwardPipeline::~ForwardPipeline()
	{
	}
}
