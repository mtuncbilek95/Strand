/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Util/ImageFormat.h>
#include <Runtime/Graphics/RHI/Util/PresentMode.h>

#include <vulkan/vulkan.h>

namespace Strand
{
	struct VkImageUtils
	{
		static VkImageType GetVkImgType(ImageType type);
		static VkFormat GetVkImgFormat(ImageFormat format);
		static VkImageUsageFlags GetVkImgUsage(ImageUsage usage);
		static VkImageAspectFlags GetVkAspectMask(ImageAspect aspect);
		static VkImageViewType GetVkViewType(ImageViewType type);
		static VkPresentModeKHR GetVkPresentMode(PresentMode mode);
		static u32 GetVkImgSize(ImageFormat type);
	};
}
