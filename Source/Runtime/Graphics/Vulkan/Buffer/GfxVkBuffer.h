/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Buffer/GfxBuffer.h>

#include <vulkan/vulkan.h>
#include <vma/vk_mem_alloc.h>

namespace Strand
{
	class GfxVkBuffer final : public GfxBuffer
	{
	public:
		GfxVkBuffer(const GfxBufferDesc& desc, GfxDevice* pDevice);
		~GfxVkBuffer() override final;

		void* Buffer() const override final;
		void Update(const ReadArray<u8>& data) override final;
		void Update(void* buffer, usize size) override final;
		void Map(const ReadArray<u8>& data) override final;
		void Map(void* buffer, usize size) override final;
		void Unmap() override final;

	private:
		VkBuffer m_buffer;
		VmaAllocation m_allocation;
		VmaAllocationInfo m_allocationInfo;

		VkPhysicalDeviceMemoryProperties m_memProps;
	};
}
