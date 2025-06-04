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