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
        VkExtent3D imageSize = { 512, 512, 1 };
        u32 mipLevels = 1;
        u32 arrayLayers = 1;
        VkImageType imageType = VK_IMAGE_TYPE_2D;
        VkFormat imageFormat = VK_FORMAT_UNDEFINED;
        VkImageUsageFlags imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        VmaMemoryUsage memoryUsage = VMA_MEMORY_USAGE_GPU_ONLY;
        VmaAllocationCreateFlags createFlags = 0;
    };

    struct ViewProps final
    {
        VkImageAspectFlags aspectFlag = VK_IMAGE_ASPECT_COLOR_BIT;
        u32 baseMipLevel = 0;
        u32 baseArrayLayer = 0;
    };

    class VImage final : public VObject
    {
    public:
        VImage(const ImageProps& desc, VDevice* pDevice);
        VImage(const ImageProps& desc, VkImage image, VDevice* pDevice);
        ~VImage() override final;

        Ref<VImageView> CreateView(const ViewProps& desc);

        inline VkImage GetVkImage() const { return m_image; }

        inline const VkExtent3D& GetExtent() const { return m_props.imageSize; }
        inline u32 GetMipLevels() const { return m_props.mipLevels; }
        inline u32 GetArrayLayers() const { return m_props.arrayLayers; }
        inline u32 GetBufferSize() const { return m_props.imageSize.width * m_props.imageSize.height * m_props.imageSize.depth * 4; }
        inline VkImageType GetType() const { return m_props.imageType; }
        inline VkFormat GetFormat() const { return m_props.imageFormat; }
        inline VkImageUsageFlags GetUsage() const { return m_props.imageUsage; }

    private:
        ImageProps m_props;
        VkImage m_image;
        VmaAllocation m_allocation;
        VmaAllocationInfo m_allocationInfo;

        b8 m_swapchainImage;
    };
}