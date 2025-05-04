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

        VDebug::VkAssert(vmaCreateBuffer(m_rootDevice->GetVkAllocator(), &bufferInfo, &allocInfo, &m_buffer, &m_allocation, &m_allocationInfo), "VBuffer");
    }

    VBuffer::~VBuffer()
    {
        if (m_buffer != VK_NULL_HANDLE)
        {
            vmaDestroyBuffer(m_rootDevice->GetVkAllocator(), m_buffer, m_allocation);
            m_buffer = VK_NULL_HANDLE;
            m_allocation = VK_NULL_HANDLE;
            m_allocationInfo.pMappedData = nullptr;
        }
    }

    void VBuffer::Update(const ReadArray<u8>& buffer, usize offset) const
    {
        if (!m_allocationInfo.pMappedData)
            return;

        std::memcpy(static_cast<u8*>(m_allocationInfo.pMappedData) + offset, buffer.Data(), buffer.SizeInBytes());

        vmaFlushAllocation(m_rootDevice->GetVkAllocator(), m_allocation, offset, buffer.SizeInBytes());
    }
}