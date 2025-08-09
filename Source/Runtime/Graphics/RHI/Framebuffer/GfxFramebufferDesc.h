/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>

namespace Strand
{
	class GfxImageView;
	class GfxRenderPass;

	struct GfxFramebufferDesc
	{
		GfxRenderPass* passRef = nullptr;
		Vector<Vector<GfxImageView*>> viewsPerFB;
		Math::Vec3u framebufferSize = { 1920, 1080, 1 };

		GfxFramebufferDesc& setPassRef(GfxRenderPass* pass) { passRef = pass; return *this; }
		GfxFramebufferDesc& addFramebufferViews(const Vector<GfxImageView*>& views) { viewsPerFB.push_back(views); return *this; }
		GfxFramebufferDesc& setFramebufferSize(const Math::Vec3u& size) { framebufferSize = size; return *this; }
	};
}
