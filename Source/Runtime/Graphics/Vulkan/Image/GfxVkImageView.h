/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Image/GfxImageView.h>
#include <Runtime/Graphics/RHI/Image/GfxImageViewDesc.h>

#include <vulkan/vulkan.h>

namespace Strand
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
