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
