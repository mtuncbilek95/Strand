#include "VkImageUtils.h"

#include <magic_enum.hpp>

namespace Flax
{
	VkImageType VkImageUtils::GetVkImgType(ImageType type)
	{
		switch (type)
		{
		case ImageType::Image1D:
			return VK_IMAGE_TYPE_1D;
		case ImageType::Image2D:
			return VK_IMAGE_TYPE_2D;
		case ImageType::Image3D:
			return VK_IMAGE_TYPE_3D;
		default:
			return VK_IMAGE_TYPE_2D;
		}
	}

	VkFormat VkImageUtils::GetVkImgFormat(ImageFormat format)
	{
		switch (format)
		{
		case ImageFormat::Undefined:
			return VK_FORMAT_UNDEFINED;

		case ImageFormat::R8_UNorm:
			return VK_FORMAT_R8_UNORM;
		case ImageFormat::R8_SNorm:
			return VK_FORMAT_R8_SNORM;
		case ImageFormat::R8_UInt:
			return VK_FORMAT_R8_UINT;
		case ImageFormat::R8_SInt:
			return VK_FORMAT_R8_SINT;
		case ImageFormat::R8_SRGB:
			return VK_FORMAT_R8_SRGB;

		case ImageFormat::R8G8_UNorm:
			return VK_FORMAT_R8G8_UNORM;
		case ImageFormat::R8G8_SNorm:
			return VK_FORMAT_R8G8_SNORM;
		case ImageFormat::R8G8_UInt:
			return VK_FORMAT_R8G8_UINT;
		case ImageFormat::R8G8_SInt:
			return VK_FORMAT_R8G8_SINT;
		case ImageFormat::R8G8_SRGB:
			return VK_FORMAT_R8G8_SRGB;

		case ImageFormat::R8G8B8_UNorm:
			return VK_FORMAT_R8G8B8_UNORM;
		case ImageFormat::R8G8B8_SNorm:
			return VK_FORMAT_R8G8B8_SNORM;
		case ImageFormat::R8G8B8_UInt:
			return VK_FORMAT_R8G8B8_UINT;
		case ImageFormat::R8G8B8_SInt:
			return VK_FORMAT_R8G8B8_SINT;
		case ImageFormat::R8G8B8_SRGB:
			return VK_FORMAT_R8G8B8_SRGB;

		case ImageFormat::R8G8B8A8_UNorm:
			return VK_FORMAT_R8G8B8A8_UNORM;
		case ImageFormat::R8G8B8A8_SNorm:
			return VK_FORMAT_R8G8B8A8_SNORM;
		case ImageFormat::R8G8B8A8_UInt:
			return VK_FORMAT_R8G8B8A8_UINT;
		case ImageFormat::R8G8B8A8_SInt:
			return VK_FORMAT_R8G8B8A8_SINT;
		case ImageFormat::R8G8B8A8_SRGB:
			return VK_FORMAT_R8G8B8A8_SRGB;

		case ImageFormat::R16_SFloat:
			return VK_FORMAT_R16_SFLOAT;
		case ImageFormat::R16G16_SFloat:
			return VK_FORMAT_R16G16_SFLOAT;
		case ImageFormat::R16G16B16_SFloat:
			return VK_FORMAT_R16G16B16_SFLOAT;
		case ImageFormat::R16G16B16A16_SFloat:
			return VK_FORMAT_R16G16B16A16_SFLOAT;

		case ImageFormat::R32_SFloat:
			return VK_FORMAT_R32_SFLOAT;
		case ImageFormat::R32G32_SFloat:
			return VK_FORMAT_R32G32_SFLOAT;
		case ImageFormat::R32G32B32_SFloat:
			return VK_FORMAT_R32G32B32_SFLOAT;
		case ImageFormat::R32G32B32A32_SFloat:
			return VK_FORMAT_R32G32B32A32_SFLOAT;

		case ImageFormat::D16_UNorm:
			return VK_FORMAT_D16_UNORM;
		case ImageFormat::D32_SFloat:
			return VK_FORMAT_D32_SFLOAT;
		case ImageFormat::S8_UInt:
			return VK_FORMAT_S8_UINT;
		case ImageFormat::D24_UNorm_S8_UInt:
			return VK_FORMAT_D24_UNORM_S8_UINT;
		case ImageFormat::D32_SFloat_S8_UInt:
			return VK_FORMAT_D32_SFLOAT_S8_UINT;

		default:
			return VK_FORMAT_UNDEFINED;
		}
	}

	VkImageUsageFlags VkImageUtils::GetVkImgUsage(ImageUsage usage)
	{
		VkImageUsageFlags flags = 0;

		for (auto u : magic_enum::enum_values<ImageUsage>())
		{
			if (HasFlag(usage, u))
			{
				switch (u)
				{
				case ImageUsage::TransferSrc:
					flags |= VK_IMAGE_USAGE_TRANSFER_SRC_BIT; break;
				case ImageUsage::TransferDst: 
					flags |= VK_IMAGE_USAGE_TRANSFER_DST_BIT; break;
				case ImageUsage::Sampled:
					flags |= VK_IMAGE_USAGE_SAMPLED_BIT; break;
				case ImageUsage::Storage:
					flags |= VK_IMAGE_USAGE_STORAGE_BIT; break;
				case ImageUsage::ColorAttachment:
					flags |= VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT; break;
				case ImageUsage::DepthStencil:
					flags |= VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT; break;
				case ImageUsage::TransientAttachment:
					flags |= VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT; break;
				case ImageUsage::InputAttachment:
					flags |= VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT; break;
				case ImageUsage::HostTransfer:
					flags |= VK_IMAGE_USAGE_HOST_TRANSFER_BIT; break;
				case ImageUsage::VideoEncodeDst:
					flags |= VK_IMAGE_USAGE_VIDEO_ENCODE_DST_BIT_KHR; break;
				case ImageUsage::VideoEncodeSrc:
					flags |= VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_BIT_KHR; break;
				case ImageUsage::VideoEncodeDpb:
					flags |= VK_IMAGE_USAGE_VIDEO_ENCODE_DPB_BIT_KHR; break;
				case ImageUsage::VideoDecodeDst:
					flags |= VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR; break;
				case ImageUsage::VideoDecodeSrc:
					flags |= VK_IMAGE_USAGE_VIDEO_DECODE_SRC_BIT_KHR; break;
				case ImageUsage::VideoDecodeDpb:
					flags |= VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR; break;
				default:
					break;
				}
			}
		}

		return flags;
	}

	VkImageAspectFlags VkImageUtils::GetVkAspectMask(ImageAspect aspect)
	{
		switch (aspect)
		{
		case ImageAspect::Color:
			return VK_IMAGE_ASPECT_COLOR_BIT;
		case ImageAspect::Depth:
			return VK_IMAGE_ASPECT_DEPTH_BIT;
		case ImageAspect::Stencil:
			return VK_IMAGE_ASPECT_STENCIL_BIT;
		case ImageAspect::Meta:
			return VK_IMAGE_ASPECT_METADATA_BIT;
		default:
			return VK_IMAGE_ASPECT_COLOR_BIT;
		}
	}

	VkImageViewType VkImageUtils::GetVkViewType(ImageViewType type)
	{
		switch (type)
		{
		case ImageViewType::View1D:        
			return VK_IMAGE_VIEW_TYPE_1D;
		case ImageViewType::View2D:        
			return VK_IMAGE_VIEW_TYPE_2D;
		case ImageViewType::View3D:        
			return VK_IMAGE_VIEW_TYPE_3D;
		case ImageViewType::ViewCube:      
			return VK_IMAGE_VIEW_TYPE_CUBE;
		case ImageViewType::View1DArray:   
			return VK_IMAGE_VIEW_TYPE_1D_ARRAY;
		case ImageViewType::View2DArray:   
			return VK_IMAGE_VIEW_TYPE_2D_ARRAY;
		case ImageViewType::View3DArray:   
			return VK_IMAGE_VIEW_TYPE_3D;
		case ImageViewType::ViewCubeArray: 
			return VK_IMAGE_VIEW_TYPE_CUBE_ARRAY;
		default:                           
			return VK_IMAGE_VIEW_TYPE_2D;
		}
	}

	VkPresentModeKHR VkImageUtils::GetVkPresentMode(PresentMode mode)
	{
		switch (mode)
		{
		case PresentMode::Fifo:
			return VK_PRESENT_MODE_FIFO_KHR;
		case PresentMode::FifoRelaxed:
			return VK_PRESENT_MODE_FIFO_RELAXED_KHR;
		case PresentMode::Immediate:
			return VK_PRESENT_MODE_IMMEDIATE_KHR;
		case PresentMode::Mailbox:
			return VK_PRESENT_MODE_MAILBOX_KHR;
		default:
			return VK_PRESENT_MODE_IMMEDIATE_KHR;
		}
	}

}
