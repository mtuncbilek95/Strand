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
#include <Runtime/Graphics/RHI/Util/PipelineFormat.h>

namespace Flax
{
    enum class AttachmentType : u8
    {
        Color,
        DepthStencil,
        Input
	};

    struct AttachmentDesc
    {
        ImageFormat format;
        AttachmentType type = AttachmentType::Color;
        ImageLayout initialLayout = ImageLayout::Undefined;
        ImageLayout finalLayout = ImageLayout::PresentSrcKHR;
        AttachmentLoad loadOp = AttachmentLoad::Clear;
        AttachmentStore storeOp = AttachmentStore::Store;

        AttachmentDesc& setFormat(ImageFormat format) { format = format; return *this; }
		AttachmentDesc& setType(AttachmentType type) { type = type; return *this; }
        AttachmentDesc& setInitialLayout(ImageLayout layout) { initialLayout = layout; return *this; }
        AttachmentDesc& setFinalLayout(ImageLayout layout) { finalLayout = layout; return *this; }
        AttachmentDesc& setLoadOp(AttachmentLoad op) { loadOp = op; return *this; }
		AttachmentDesc& setStoreOp(AttachmentStore op) { storeOp = op; return *this; }
    };

    struct SubpassDesc
    {
        Vector<u32> colorAttachmentIndices;
        u32 depthAttachmentIndex = u32_max;
        Vector<u32> inputAttachmentIndices;
        PipelineType bindPoint;

		SubpassDesc& addColorAttachment(u32 index) { colorAttachmentIndices.push_back(index); return *this; }
		SubpassDesc& setDepthAttachment(u32 index) { depthAttachmentIndex = index; return *this; }
		SubpassDesc& addInputAttachment(u32 index) { inputAttachmentIndices.push_back(index); return *this; }
		SubpassDesc& setBindPoint(PipelineType type) { bindPoint = type; return *this; }
    };

	struct GfxRenderPassDesc
	{
        Vector<AttachmentDesc> attachments;
        Vector<SubpassDesc> subpasses;

        GfxRenderPassDesc& addAttachment(const AttachmentDesc& attachment) { attachments.push_back(attachment); return *this; }
		GfxRenderPassDesc& addSubpass(const SubpassDesc& subpass) { subpasses.push_back(subpass); return *this; }
	};
}
