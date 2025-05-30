#include "FvkImage.h"

#include <Runtime/Graphics/Context/FvkContext.h>
#include <Runtime/Graphics/Image/FvkImageView.h>

#include <Volk/volk.h>

namespace Flax
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

	FvkImage::FvkImage(const ImageProps& desc) : m_props(desc),
		m_isSwapchain(false)
	{
        auto& context = FvkContext::Get();

        VkImageCreateInfo imageInfo = {};
        imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        imageInfo.imageType = desc.imgType;
        imageInfo.extent = { desc.imgSize.x , desc.imgSize.y, desc.imgSize.z };
        imageInfo.mipLevels = desc.mipLevels;
        imageInfo.arrayLayers = desc.arrayLayers;
        imageInfo.format = desc.imgFormat;
        imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
        imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        imageInfo.usage = desc.imgUsage;
        imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
        imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        VmaAllocationCreateInfo allocInfo = {};
        allocInfo.usage = desc.memUsage;
        allocInfo.flags = desc.memFlags;

        FvkDebug::Assert(vmaCreateImage(context.Allocator(), &imageInfo, &allocInfo, &m_image, &m_allocation, &m_allocationInfo), "FvkImage");
	}

	FvkImage::FvkImage(const ImageProps& desc, VkImage handle) : m_props(desc),
		m_isSwapchain(true), m_image(handle), m_allocation(nullptr), m_allocationInfo(VmaAllocationInfo())
	{
	}

	FvkImage::~FvkImage()
	{
        auto& context = FvkContext::Get();

		if (m_allocation && !m_isSwapchain)
		{
			vmaDestroyImage(context.Allocator(), m_image, m_allocation);
			m_allocation = nullptr;
		}
	}

	Ref<FvkImageView> FvkImage::CreateView(const ViewProps& desc)
	{
		ImageViewProps viewProp(this,
			CastType(m_props.imgType, m_props.arrayLayers),
			desc.aspectMask, desc.baseMipLevel, desc.baseArrayLayer);

		return NewRef<FvkImageView>(viewProp);
	}
}