/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>

namespace Flax
{
	struct ShaderCompiler final
	{
		ShaderCompiler() = delete; // Make a static utility class

		static ReadArray<u32> CompileShader(const String& shaderPath, const String& includePath = "", const String& entryPoint = "main");
	};
}