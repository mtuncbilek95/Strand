/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Image/GfxImageView.h>
#include <Runtime/Graphics/RHI/Image/GfxImageViewDesc.h>

#include <vulkan/vulkan.h>

namespace Flax
{
	class GfxVkImageView : public GfxImageView
	{
	public:
		GfxVkImageView(const GfxImageViewDesc& desc, GfxDevice* pDevice);
		~GfxVkImageView() override final;

		void* Image() const override final;
		void* View() const override final;

	private:
		VkImage m_image;
		VkImageView m_view;
	};
}
