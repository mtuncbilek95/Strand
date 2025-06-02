/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Util/SamplerFormat.h>

#include <vulkan/vulkan.h>

namespace Flax
{
	struct VkSamplerUtils
	{
		static VkFilter GetVkFilter(SamplerFilter filter);
		static VkSamplerMipmapMode GetVkMipMap(SamplerMipMap mode);
		static VkSamplerAddressMode GetVkSamplerAddress(SamplerAddress address);
		static VkBorderColor GetVkColor(BorderColor color);
	};
}
