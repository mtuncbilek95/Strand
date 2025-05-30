#include "FvkImageView.h"

#include <Volk/volk.h>

#include <Runtime/Graphics/Context/FvkContext.h>

namespace Flax
{
    FvkImageView::FvkImageView(const ImageViewProps& desc) : m_props(desc)
    {
		auto& context = FvkContext::Get();

		VkImageViewCreateInfo viewInfo = { VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO };
		viewInfo.image = desc.ownerImage->GetVkImage();
		viewInfo.viewType = desc.viewType;
		viewInfo.format = desc.ownerImage->GetFormat();

		viewInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		viewInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		viewInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		viewInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

		viewInfo.subresourceRange.aspectMask = desc.aspectFlag;
		viewInfo.subresourceRange.baseMipLevel = desc.baseMipLevel;
		viewInfo.subresourceRange.levelCount = desc.ownerImage->GetMipLevels();
		viewInfo.subresourceRange.baseArrayLayer = desc.baseArrayLayer;
		viewInfo.subresourceRange.layerCount = desc.ownerImage->GetArrayLayers();

		FvkDebug::Assert(vkCreateImageView(context.Device(), &viewInfo, nullptr, &m_view), "FvkImageView");
    }

    FvkImageView::~FvkImageView()
    {
		auto& context = FvkContext::Get();

        if (m_view != VK_NULL_HANDLE)
        {
            vkDestroyImageView(context.Device(), m_view, nullptr);
            m_view = VK_NULL_HANDLE;
        }
    }
}