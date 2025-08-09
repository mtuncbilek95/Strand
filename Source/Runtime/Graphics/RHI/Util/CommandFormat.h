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
	enum class CommandPoolFlags
	{
		ResetCommandBuffer = 1 << 0
	};

	enum class CommandLevel
	{
		Primary,
		Secondary
	};

	enum class CommandBufferUsage
	{
		OneTimeSubmit = 1 << 0,
		RenderPassContinue = 1 << 1,
		SimultaneousUse = 1 << 2
	};

	enum class SubpassContent
	{
		ContentsInline,
		SecondaryBuffer,
		InlineAndSecondaryBuffer
	};
}