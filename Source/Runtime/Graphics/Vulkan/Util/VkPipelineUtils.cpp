#include "VkPipelineUtils.h"

namespace Flax
{
	VkCompareOp VkPipelineUtils::GetVkCompareOp(CompareOp op)
	{
		switch (op)
		{
		case CompareOp::Never:
			return VK_COMPARE_OP_NEVER;
		case CompareOp::Less:
			return VK_COMPARE_OP_LESS;
		case CompareOp::Equal:
			return VK_COMPARE_OP_EQUAL;
		case CompareOp::LesserEqual:
			return VK_COMPARE_OP_LESS_OR_EQUAL;
		case CompareOp::Greater:
			return VK_COMPARE_OP_GREATER;
		case CompareOp::NotEqual:
			return VK_COMPARE_OP_NOT_EQUAL;
		case CompareOp::GreaterEqual:
			return VK_COMPARE_OP_GREATER_OR_EQUAL;
		case CompareOp::Always:
		default:
			return VK_COMPARE_OP_ALWAYS;
		}
	}

	VkPipelineBindPoint VkPipelineUtils::GetVkBindPoint(PipelineType type)
	{
		switch (type)
		{
		case PipelineType::Graphics:
			return VK_PIPELINE_BIND_POINT_GRAPHICS;
		case PipelineType::Compute:
			return VK_PIPELINE_BIND_POINT_COMPUTE;
		case PipelineType::Raytracing:
			return VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR;
		default:
			return VK_PIPELINE_BIND_POINT_GRAPHICS;
		}
	}

	VkImageLayout VkPipelineUtils::GetVkImgLayout(ImageLayout layout)
	{
		switch (layout)
		{
		case ImageLayout::Undefined:
			return VK_IMAGE_LAYOUT_UNDEFINED;
		case ImageLayout::General:
			return VK_IMAGE_LAYOUT_GENERAL;
		case ImageLayout::ColorAttachmentOptimal:
			return VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		case ImageLayout::DepthStencilAttachmentOptimal:
			return VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
		case ImageLayout::DepthStencilReadOnlyOptimal:
			return VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
		case ImageLayout::ShaderReadOnlyOptimal:
			return VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		case ImageLayout::TransferSrcOptimal:
			return VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
		case ImageLayout::TransferDstOptimal:
			return VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
		case ImageLayout::Preinitialized:
			return VK_IMAGE_LAYOUT_PREINITIALIZED;
		case ImageLayout::PresentSrcKHR:
			return VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
		default:
			return VK_IMAGE_LAYOUT_UNDEFINED;
		}
	}

	VkAttachmentStoreOp VkPipelineUtils::GetVkStoreOp(AttachmentStore op)
	{
		switch (op)
		{
		case AttachmentStore::DontCare:
			return VK_ATTACHMENT_STORE_OP_DONT_CARE;
		case AttachmentStore::Store:
			return VK_ATTACHMENT_STORE_OP_STORE;
		default:
			return VK_ATTACHMENT_STORE_OP_DONT_CARE;
		}
	}

	VkAttachmentLoadOp VkPipelineUtils::GetVkLoadOp(AttachmentLoad op)
	{
		switch (op)
		{
		case AttachmentLoad::Load:
			return VK_ATTACHMENT_LOAD_OP_LOAD;
		case AttachmentLoad::Clear:
			return VK_ATTACHMENT_LOAD_OP_CLEAR;
		case AttachmentLoad::DontCare:
			return VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		default:
			return VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		}
	}

}
