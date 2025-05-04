/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Vulkan/Object/VObject.h>

namespace Flax
{
    struct BufferProps final
    {
        usize sizeInBytes = 0;
        VkBufferUsageFlags usage = 0;

        VmaMemoryUsage memUsage;
        VmaAllocationCreateFlags allocFlags = 0;
    };

    class VBuffer final : public VObject
    {
    public:
        VBuffer(const BufferProps& desc, VDevice* pDevice);
        ~VBuffer() override final;

        inline VkBuffer GetVkBuffer() const { return m_buffer; }
        inline usize GetTotalSize() const { return m_props.sizeInBytes; }
        inline u8* GetMappedData() const { return static_cast<u8*>(m_allocationInfo.pMappedData); }

        void Update(const ReadArray<u8>& buffer, usize offset = 0) const;

    private:
        BufferProps m_props;

        VkBuffer m_buffer;
        VmaAllocation m_allocation;
        VmaAllocationInfo m_allocationInfo;
    };
}