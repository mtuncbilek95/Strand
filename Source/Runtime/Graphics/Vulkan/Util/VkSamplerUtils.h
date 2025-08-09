/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Util/SamplerFormat.h>

#include <vulkan/vulkan.h>

namespace Strand
{
	struct VkSamplerUtils
	{
		static VkFilter GetVkFilter(SamplerFilter filter);
		static VkSamplerMipmapMode GetVkMipMap(SamplerMipMap mode);
		static VkSamplerAddressMode GetVkSamplerAddress(SamplerAddress address);
		static VkBorderColor GetVkColor(BorderColor color);
	};
}
