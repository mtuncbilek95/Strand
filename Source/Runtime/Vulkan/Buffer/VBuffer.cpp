#include "VBuffer.h"

#include <Runtime/Vulkan/Device/VDevice.h>
#include <Runtime/Vulkan/Debug/VDebug.h>

namespace Flax
{
    VBuffer::VBuffer(const BufferProps& desc, VDevice* pDevice) : VObject(pDevice), m_props(desc)
    {
        VkBufferCreateInfo bufferInfo = {};
        bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferInfo.size = desc.sizeInBytes;
        bufferInfo.usage = desc.usage;
        bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        VmaAllocationCreateInfo allocInfo{};
        allocInfo.usage = desc.memUsage;
        allocInfo.flags = desc.allocFlags;

        VDebug::VkAssert(vmaCreateBuffer(GetRoot()->GetVkAllocator(), &bufferInfo, &allocInfo, &m_buffer, &m_allocation, &m_allocationInfo), "VBuffer");
    }

    VBuffer::~VBuffer()
    {
        if (m_buffer != VK_NULL_HANDLE)
        {
            vmaDestroyBuffer(GetRoot()->GetVkAllocator(), m_buffer, m_allocation);
            m_buffer = VK_NULL_HANDLE;
            m_allocation = VK_NULL_HANDLE;
            m_allocationInfo.pMappedData = nullptr;
        }
    }

    void VBuffer::Update(const ReadArray<u8>& buffer, usize offset) const
    {
        if (m_props.memUsage & VMA_MEMORY_USAGE_AUTO_PREFER_HOST)
        {
            void* data = m_allocationInfo.pMappedData;
            b8 mappedHost = false;

            if (!data)
            {
                VDebug::VkAssert(vmaMapMemory(GetRoot()->GetVkAllocator(), m_allocation, &data), "VBuffer");
				mappedHost = true;
            }

			std::memcpy(static_cast<u8*>(data) + offset, buffer.Data(), buffer.SizeInBytes());

            VkMemoryPropertyFlags memProps = {};
			vmaGetMemoryTypeProperties(GetRoot()->GetVkAllocator(), m_allocationInfo.memoryType, &memProps);

            if (!(memProps & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT))
                vmaFlushAllocation(GetRoot()->GetVkAllocator(), m_allocation, offset, buffer.Size());

            if(mappedHost)
				vmaUnmapMemory(GetRoot()->GetVkAllocator(), m_allocation);
        }
    }

    void VBuffer::Update(void* buffer, usize size, usize offset) const
    {
        if (m_props.memUsage & VMA_MEMORY_USAGE_AUTO_PREFER_HOST)
        {
            void* data = m_allocationInfo.pMappedData;
            b8 mappedHost = false;

            if (!data)
            {
                VDebug::VkAssert(vmaMapMemory(GetRoot()->GetVkAllocator(), m_allocation, &data), "VBuffer");
                mappedHost = true;
            }

            std::memcpy(static_cast<u8*>(data) + offset, buffer, size);

            VkMemoryPropertyFlags memProps = {};
            vmaGetMemoryTypeProperties(GetRoot()->GetVkAllocator(), m_allocationInfo.memoryType, &memProps);

            if (!(memProps & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT))
                vmaFlushAllocation(GetRoot()->GetVkAllocator(), m_allocation, offset, size);

            if (mappedHost)
                vmaUnmapMemory(GetRoot()->GetVkAllocator(), m_allocation);
        }
    }
}