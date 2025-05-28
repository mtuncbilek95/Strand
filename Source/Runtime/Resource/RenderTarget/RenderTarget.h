/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Resource/IResource.h>
#include <Runtime/Vulkan/Image/VImage.h>
#include <Runtime/Vulkan/Image/VImageView.h>
#include <Runtime/Vulkan/RenderPass/VRenderPass.h>
#include <Runtime/Vulkan/Framebuffer/VFramebuffer.h>

namespace Flax
{
	enum class RenderTargetType
	{
		Draw,
		Intermediate,
		ShadowMap,
		Compute,
		Custom
	};

	struct AttachmentOps
	{
		VkAttachmentLoadOp loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		VkAttachmentStoreOp storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		VkImageLayout initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		VkImageLayout finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
	};

	struct RenderTargetProps final
	{
		RenderTargetType type = RenderTargetType::Draw;
		Math::Vec2u size;
		VkFormat format = VK_FORMAT_UNDEFINED;

		AttachmentOps attachment;

		b8 sampled = true;
		b8 asRenderTarget = true;

		Ref<VImage> externalImage = nullptr;
		Ref<VImageView> externalView = nullptr;
	};

	class RenderTarget
	{
	public:
		RenderTarget(const RenderTargetProps& desc);
		~RenderTarget();

		Math::Vec2u GetSize() const { return m_props.size; }

	private:
		RenderTargetProps m_props;

		Ref<VRenderPass> m_renderPass;
		Ref<VFramebuffer> m_framebuffer;

		Ref<VImage> m_image;
		Ref<VImageView> m_view;
	};
}
