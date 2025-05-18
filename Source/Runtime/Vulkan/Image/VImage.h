/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Vulkan/Object/VObject.h>

namespace Flax
{
	class VImageView;

	struct ImageProps final
	{
		Math::Vec3u imgSize = Math::Vec3u(0, 0, 1);
		u32 mipLevels = 1;
		u32 arrayLayers = 1;
		VkImageType imgType = VK_IMAGE_TYPE_2D;
		VkFormat imgFormat = VK_FORMAT_UNDEFINED;
		VkImageUsageFlags imgUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		VmaMemoryUsage memUsage = VMA_MEMORY_USAGE_AUTO_PREFER_DEVICE;
		VmaAllocationCreateFlags memFlags = VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT;
	};

	struct ViewProps final
	{
		VkImageAspectFlags aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		u32 baseMipLevel = 0;
		u32 baseArrayLayer = 0;
	};

	class VImage final : public VObject
	{
	public:
		VImage(const ImageProps& desc, VDevice* pDevice);
		VImage(const ImageProps& desc, VkImage handle, VDevice* pDevice);
		~VImage() override final;

		Ref<VImageView> CreateView(const ViewProps& desc);

		inline VkImage GetVkImage() const { return m_image; }
		inline Math::Vec3u GetSize() const { return m_props.imgSize; }
		inline u32 GetMipLevels() const { return m_props.mipLevels; }
		inline u32 GetArrayLayers() const { return m_props.arrayLayers; }
		inline u32 GetBufferSize() const { return m_props.imgSize.x * m_props.imgSize.y * m_props.imgSize.z * 4; }
		inline VkImageType GetType() const { return m_props.imgType; }
		inline VkFormat GetFormat() const { return m_props.imgFormat; }
		inline VkImageUsageFlags GetUsage() const { return m_props.imgUsage; }

		inline VmaMemoryUsage GetMemoryUsage() const { return m_props.memUsage; }
		inline VmaAllocationCreateFlags GetMemoryFlags() const { return m_props.memFlags; }

	private:
		ImageProps m_props;

		VkImage m_image;

		VmaAllocation m_allocation;
		VmaAllocationInfo m_allocationInfo;

		b8 m_isSwapchain;
	};
}