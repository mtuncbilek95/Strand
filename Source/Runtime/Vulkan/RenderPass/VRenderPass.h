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
    enum class AttachmentType : u8
    {
        Color,
        Depth
    };

    struct AttachmentDesc
    {
        VkFormat format;
        AttachmentType type = AttachmentType::Color;
        VkImageLayout initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        VkImageLayout finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
        VkAttachmentLoadOp loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        VkAttachmentStoreOp storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    };

    struct SubpassDesc
    {
        Vector<u32> colorAttachmentIndices;
        u32 depthAttachmentIndex = u32_max;
        Vector<u32> inputAttachmentIndices;
        VkPipelineBindPoint bindPoint;
    };

    struct RenderPassProps
    {
        Vector<AttachmentDesc> attachments;
        Vector<SubpassDesc> subpasses;
    };

    class VRenderPass final : public VObject
    {
    public:
        VRenderPass(const RenderPassProps& desc, VDevice* pDevice);
        ~VRenderPass() override final;

        inline VkRenderPass GetVkRenderPass() const { return m_renderPass; }

    private:
        RenderPassProps m_props;

        VkRenderPass m_renderPass;
    };
}