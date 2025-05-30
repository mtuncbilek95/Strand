#include "FvkBuffer.h"

#include <Runtime/Graphics/Context/FvkContext.h>

namespace Flax
{
    FvkBuffer::FvkBuffer(const BufferProps& desc) : m_props(desc)
    {
        auto& context = FvkContext::Get();

        VkBufferCreateInfo bufferInfo = {};
        bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferInfo.size = desc.sizeInBytes;
        bufferInfo.usage = desc.usage;
        bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        VmaAllocationCreateInfo allocInfo{};
        allocInfo.usage = desc.memUsage;
        allocInfo.flags = desc.allocFlags;

        FvkDebug::Assert(vmaCreateBuffer(context.Allocator(), &bufferInfo, &allocInfo, &m_buffer, &m_allocation, &m_allocationInfo), "FvkBuffer");
    }

    FvkBuffer::~FvkBuffer()
    {
        auto& context = FvkContext::Get();

        if (m_buffer != VK_NULL_HANDLE)
        {
            vmaDestroyBuffer(context.Allocator(), m_buffer, m_allocation);
            m_buffer = VK_NULL_HANDLE;
            m_allocation = VK_NULL_HANDLE;
            m_allocationInfo.pMappedData = nullptr;
        }
    }

    void FvkBuffer::Update(const ReadArray<u8>& buffer, usize offset) const
    {
        auto& context = FvkContext::Get();

        if (m_props.memUsage & VMA_MEMORY_USAGE_AUTO_PREFER_HOST)
        {
            void* data = m_allocationInfo.pMappedData;
            b8 mappedHost = false;

            if (!data)
            {
                FvkDebug::Assert(vmaMapMemory(context.Allocator(), m_allocation, &data), "FvkBuffer");
                mappedHost = true;
            }

            std::memcpy(static_cast<u8*>(data) + offset, buffer.Data(), buffer.SizeInBytes());

            VkMemoryPropertyFlags memProps = {};
            vmaGetMemoryTypeProperties(context.Allocator(), m_allocationInfo.memoryType, &memProps);

            if (!(memProps & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT))
                vmaFlushAllocation(context.Allocator(), m_allocation, offset, buffer.Size());

            if (mappedHost)
                vmaUnmapMemory(context.Allocator(), m_allocation);
        }
    }

    void FvkBuffer::Update(void* buffer, usize size, usize offset) const
    {
        auto& context = FvkContext::Get();

        if (m_props.memUsage & VMA_MEMORY_USAGE_AUTO_PREFER_HOST)
        {
            void* data = m_allocationInfo.pMappedData;
            b8 mappedHost = false;

            if (!data)
            {
                FvkDebug::Assert(vmaMapMemory(context.Allocator(), m_allocation, &data), "FvkBuffer");
                mappedHost = true;
            }

            std::memcpy(static_cast<u8*>(data) + offset, buffer, size);

            VkMemoryPropertyFlags memProps = {};
            vmaGetMemoryTypeProperties(context.Allocator(), m_allocationInfo.memoryType, &memProps);

            if (!(memProps & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT))
                vmaFlushAllocation(context.Allocator(), m_allocation, offset, size);

            if (mappedHost)
                vmaUnmapMemory(context.Allocator(), m_allocation);
        }
    }
}