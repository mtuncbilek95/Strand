/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Image/GfxImage.h>

#include <vulkan/vulkan.h>
#include <vma/vk_mem_alloc.h>

namespace Strand
{
	class GfxImageView;

	class GfxVkImage final : public GfxImage
	{
	public:
		GfxVkImage(const GfxImageDesc& desc, GfxDevice* pDevice);
		GfxVkImage(const GfxImageDesc& desc, GfxDevice* pDevice, void* apiImage);
		~GfxVkImage() override final;

		void* Image() const override final;
		Ref<GfxImageView> CreateView(const GfxViewDesc& desc) override final;

	private:
		VkImage m_image;

		VmaAllocation m_allocation;
		VmaAllocationInfo m_allocationInfo;
	};
}
