/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>

namespace Strand
{
	struct ShaderCompiler final
	{
		ShaderCompiler() = delete; // Make a static utility class

		static ReadArray<u32> CompileShader(const String& shaderPath, const String& includePath = "", const String& entryPoint = "main");
	};
}