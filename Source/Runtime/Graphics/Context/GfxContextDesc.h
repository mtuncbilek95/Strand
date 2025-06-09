/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>

#include <Runtime/Graphics/RHI/Instance/GfxType.h>
#include <Runtime/Graphics/RHI/Util/ImageFormat.h>
#include <Runtime/Graphics/RHI/Util/PresentMode.h>

namespace Flax
{
	struct GfxContextDesc
	{
		String appName = "Flax";
		Math::Vec3u appVer = { 1, 0, 0 };
		GfxType type = GfxType::Vulkan;

		u32 graphicsQueueCount = 1;
		u32 computeQueueCount = 1;
		u32 transferQueueCount = 1;

		ImageFormat colorFormat = ImageFormat::R8G8B8A8_UNorm;
		ImageFormat depthFormat = ImageFormat::D32_SFloat;

		u32 imageCount = 2;
		PresentMode presentMode = PresentMode::Fifo;

		Math::Vec2u windowSize = { 1280, 720 };
		void* windowHandle = nullptr;

		GfxContextDesc& setAppName(const String& name) { appName = name; return *this; }
		GfxContextDesc& setAppVersion(const Math::Vec3u& version) { appVer = version; return *this; }
		GfxContextDesc& setAPIType(GfxType gfxType) { type = gfxType; return *this; }
		GfxContextDesc& setGraphicsQueueCount(u32 count) { graphicsQueueCount = count; return *this; }
		GfxContextDesc& setComputeQueueCount(u32 count) { computeQueueCount = count; return *this; }
		GfxContextDesc& setTransferQueueCount(u32 count) { transferQueueCount = count; return *this; }
		GfxContextDesc& setColorFormat(ImageFormat format) { colorFormat = format; return *this; }
		GfxContextDesc& setDepthFormat(ImageFormat format) { depthFormat = format; return *this; }
		GfxContextDesc& setImageCount(u32 count) { imageCount = count; return *this; }
		GfxContextDesc& setPresentMode(PresentMode mode) { presentMode = mode; return *this; }
		GfxContextDesc& setWindowSize(const Math::Vec2u& size) { windowSize = size; return *this; }
		GfxContextDesc& setWindowHandle(void* handle) { windowHandle = handle; return *this; }
	};
}
