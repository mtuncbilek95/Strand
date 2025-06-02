/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Util/ImageFormat.h>
#include <Runtime/Graphics/RHI/Util/PresentMode.h>

#include <vulkan/vulkan.h>

namespace Flax
{
	struct VkImageUtils
	{
		static VkImageType GetVkImgType(ImageType type);
		static VkFormat GetVkImgFormat(ImageFormat format);
		static VkImageUsageFlags GetVkImgUsage(ImageUsage usage);
		static VkImageAspectFlags GetVkAspectMask(ImageAspect aspect);
		static VkImageViewType GetVkViewType(ImageViewType type);
		static VkPresentModeKHR GetVkPresentMode(PresentMode mode);
	};
}
