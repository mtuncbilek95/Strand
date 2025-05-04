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
#include <Runtime/Vulkan/Image/VImage.h>

namespace Flax
{
    struct ImageViewProps final
    {
        VImage* ownerImage = nullptr;
        VkImageViewType viewType = VK_IMAGE_VIEW_TYPE_2D;
        VkImageAspectFlags aspectFlag = VK_IMAGE_ASPECT_COLOR_BIT;
        u32 baseMipLevel = 0;
        u32 baseArrayLayer = 0;
    };

    class VImageView final : public VObject
    {
    public:
        VImageView(const ImageViewProps& desc, VDevice* pDevice);
        ~VImageView() override final;

        inline VkImageView GetVkView() const { return m_view; }
        inline VkImage GetVkImage() const { return m_props.ownerImage->GetVkImage(); }
        inline VkFormat GetVkFormat() const { return m_props.ownerImage->GetFormat(); }
        inline const VkExtent3D& GetVkExtent() const { return m_props.ownerImage->GetExtent(); }

        inline VImage* GetImage() const { return m_props.ownerImage; }
        inline VkImageViewType GetType() const { return m_props.viewType; }
        inline VkImageAspectFlags GetAspect() const { return m_props.aspectFlag; }
        inline u32 GetBaseMipLevel() const { return m_props.baseMipLevel; }
        inline u32 GetBaseArrayLayer() const { return m_props.baseArrayLayer; }

    private:
        ImageViewProps m_props;

        VkImageView m_view;
    };
}