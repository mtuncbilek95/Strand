/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Util/PresentMode.h>
#include <Runtime/Graphics/RHI/Util/ImageFormat.h>

namespace Strand
{
	class GfxQueue;

	struct GfxSwapchainDesc
	{
		Math::Vec2u imageSize = { 1280, 720 };
		u8 imageCount = 2;
		ImageFormat format = ImageFormat::R8G8B8A8_UNorm;
		PresentMode presentMode = PresentMode::Fifo;
		GfxQueue* graphicsQueue = nullptr;
		void* windowHandler = nullptr;

		GfxSwapchainDesc& setImageSize(const Math::Vec2u& size) { imageSize = size; return *this; }
		GfxSwapchainDesc& setImageCount(u8 count) { imageCount = count; return *this; }
		GfxSwapchainDesc& setFormat(ImageFormat fmt) { format = fmt; return *this; }
		GfxSwapchainDesc& setPresentMode(PresentMode mode) { presentMode = mode; return *this; }
		GfxSwapchainDesc& setGraphicsQueue(GfxQueue* queue) { graphicsQueue = queue; return *this; }
		GfxSwapchainDesc& setWindowHandler(void* handler) { windowHandler = handler; return *this; }
	};
}