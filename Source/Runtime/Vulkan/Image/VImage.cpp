#include "VImage.h"

#include <Runtime/Vulkan/Device/VDevice.h>
#include <Runtime/Vulkan/Debug/VDebug.h>
#include <Runtime/Vulkan/Image/VImageView.h>

namespace Flax
{
    namespace ViewHelper
    {
        static VkImageViewType CastType(VkImageType type, u32 layerCount)
        {
            if (type & VK_IMAGE_TYPE_2D)
            {
                if (layerCount == 6)
                    return VK_IMAGE_VIEW_TYPE_CUBE;
                else if (layerCount > 6 && layerCount % 6 == 0)
                    return VK_IMAGE_VIEW_TYPE_CUBE_ARRAY;
            }

            switch (type)
            {
            case VK_IMAGE_TYPE_1D:
                return layerCount > 1 ? VK_IMAGE_VIEW_TYPE_1D_ARRAY : VK_IMAGE_VIEW_TYPE_1D;
            case VK_IMAGE_TYPE_2D:
                return layerCount > 1 ? VK_IMAGE_VIEW_TYPE_2D_ARRAY : VK_IMAGE_VIEW_TYPE_2D;
            case VK_IMAGE_TYPE_3D:
                return layerCount > 1 ? VK_IMAGE_VIEW_TYPE_2D_ARRAY : VK_IMAGE_VIEW_TYPE_3D;
            default:
                Log::Error(LogType::Render, "You're using wrong vk::ImageType or vk::ImageViewType");
                break;
            }

            return VK_IMAGE_VIEW_TYPE_2D;
        }
    }

    VImage::VImage(const ImageProps& desc, VDevice* pDevice) : VObject(pDevice), m_props(desc), m_swapchainImage(false)
    {
        VkImageCreateInfo imageInfo = {};
        imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        imageInfo.imageType = desc.imageType;
        imageInfo.extent = desc.imageSize;
        imageInfo.mipLevels = desc.mipLevels;
        imageInfo.arrayLayers = desc.arrayLayers;
        imageInfo.format = desc.imageFormat;
        imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
        imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        imageInfo.usage = desc.imageUsage;
        imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
        imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        VmaAllocationCreateInfo allocInfo = {};
        allocInfo.usage = desc.memoryUsage;
        allocInfo.flags = desc.createFlags;

        VDebug::VkAssert(vmaCreateImage(m_rootDevice->GetVkAllocator(), &imageInfo, &allocInfo, &m_image, &m_allocation, &m_allocationInfo), "VImage");
    }

    VImage::VImage(const ImageProps& desc, VkImage image, VDevice* pDevice) : VObject(pDevice), m_props(desc), m_image(image), m_swapchainImage(true),
        m_allocation(VK_NULL_HANDLE), m_allocationInfo(VmaAllocationInfo())
    {
    }

    VImage::~VImage()
    {
        if (m_image != VK_NULL_HANDLE && !m_swapchainImage)
        {
            vmaDestroyImage(m_rootDevice->GetVkAllocator(), m_image, m_allocation);
            m_image = VK_NULL_HANDLE;
            m_allocation = VK_NULL_HANDLE;
            m_allocationInfo.pMappedData = nullptr;
        }
    }

    Ref<VImageView> VImage::CreateView(const ViewProps& desc)
    {
        ImageViewProps viewProp(this,
			ViewHelper::CastType(m_props.imageType, m_props.arrayLayers),
			desc.aspectFlag, desc.baseMipLevel, desc.baseArrayLayer);

		return MakeShared<VImageView>(viewProp, m_rootDevice);
    }
}