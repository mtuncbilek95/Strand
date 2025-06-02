/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Object/GfxObject.h>
#include <Runtime/Graphics/RHI/Image/GfxImageDesc.h>

namespace Flax
{
	class GfxImageView;

	class GfxImage : public GfxObject
	{
	public:
		GfxImage(const GfxImageDesc& desc, GfxDevice* pDevice);
		GfxImage(const GfxImageDesc& desc, GfxDevice* pDevice, void* apiImage);
		virtual ~GfxImage() override = default;

		virtual void* Image() const = 0;
		virtual Ref<GfxImageView> CreateView(const GfxViewDesc& desc) = 0;

		const Math::Vec3u& ImgSize() const { return m_desc.imgSize; }
		u32 MipLevels() const { return m_desc.mipLevels; }
		u32 ArrayLayers() const { return m_desc.arrayLayers; }
		ImageType ImageType() const { return m_desc.type; }
		ImageFormat ImageFormat() const { return m_desc.format; }
		ImageUsage ImageUsage() const { return m_desc.usage; }

		b8 IsSwapchain() const { return m_isSwapchain; }

	private:
		GfxImageDesc m_desc;
		b8 m_isSwapchain;
	};
}
