/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>

namespace Flax
{
	class VRenderPass;
	class VFramebuffer;
	class VImage;
	class VImageView;

	struct RenderTargetProps final
	{

	};

	class RenderTarget
	{
	public:
		RenderTarget(const RenderTargetProps& desc);
		~RenderTarget();

		Math::Vec2u GetSize() const;

	private:
		RenderTargetProps m_props;

		Ref<VRenderPass> m_renderPass;
		Ref<VFramebuffer> m_framebuffer;

		Ref<VImage> m_image;
		Ref<VImageView> m_view;
	};
}
