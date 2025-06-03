/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Util/PipelineFormat.h>
#include <Runtime/Graphics/RHI/Util/ImageFormat.h>
#include <Runtime/Graphics/RHI/Util/ShaderStage.h>

#include <vulkan/vulkan.h>

namespace Flax
{
	struct VkPipelineUtils
	{
		static VkCompareOp GetVkCompareOp(CompareOp op);
		static VkPipelineBindPoint GetVkBindPoint(PipelineType type);
		static VkImageLayout GetVkImgLayout(ImageLayout layout);
		static VkAttachmentStoreOp GetVkStoreOp(AttachmentStore op);
		static VkAttachmentLoadOp GetVkLoadOp(AttachmentLoad op);
		static VkShaderStageFlags GetShaderType(ShaderStage stage);
		static VkShaderStageFlagBits GetShaderTypeBit(ShaderStage stage);
		static VkPrimitiveTopology GetVkTopo(PrimitiveTopology topo);
	};
}
