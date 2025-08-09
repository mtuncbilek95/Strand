/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>

#include <vulkan/vulkan.h>

namespace Strand
{
	struct VDebug final
	{
		static void VkAssert(VkResult result, const String& objectTitle);
	};
}