#include "VkPipelineUtils.h"

#include <magic_enum.hpp>

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

	VkShaderStageFlags VkPipelineUtils::GetShaderType(ShaderStage stage)
	{
		VkShaderStageFlags flags = 0;

		for (auto s : magic_enum::enum_values<ShaderStage>())
		{
			if (IsSameFlag(s, ShaderStage::All))
				return VK_SHADER_STAGE_ALL;

			if (HasFlag(stage, s))
			{
				switch (s)
				{
				case ShaderStage::Vertex:
					flags |= VK_SHADER_STAGE_VERTEX_BIT; break;
				case ShaderStage::TessControl:
					flags |= VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT; break;
				case ShaderStage::TessEval:
					flags |= VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT; break;
				case ShaderStage::Geometry:
					flags |= VK_SHADER_STAGE_GEOMETRY_BIT; break;
				case ShaderStage::Fragment:
					flags |= VK_SHADER_STAGE_FRAGMENT_BIT; break;
				case ShaderStage::Compute:
					flags |= VK_SHADER_STAGE_COMPUTE_BIT; break;
				case ShaderStage::Raygen:
					flags |= VK_SHADER_STAGE_RAYGEN_BIT_KHR; break;
				case ShaderStage::Anyhit:
					flags |= VK_SHADER_STAGE_ANY_HIT_BIT_KHR; break;
				case ShaderStage::ClosestHit:
					flags |= VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR; break;
				case ShaderStage::Miss:
					flags |= VK_SHADER_STAGE_MISS_BIT_KHR; break;
				case ShaderStage::Intersection:
					flags |= VK_SHADER_STAGE_INTERSECTION_BIT_KHR; break;
				case ShaderStage::Callable:
					flags |= VK_SHADER_STAGE_CALLABLE_BIT_KHR; break;
				case ShaderStage::Task:
					flags |= VK_SHADER_STAGE_TASK_BIT_EXT; break;
				case ShaderStage::Mesh:
					flags |= VK_SHADER_STAGE_MESH_BIT_EXT; break;
				default: break;
				}
			}
		}

		return flags;
	}

	VkShaderStageFlagBits VkPipelineUtils::GetShaderTypeBit(ShaderStage stage)
	{
		switch (stage)
		{
		case ShaderStage::Vertex:
			return VK_SHADER_STAGE_VERTEX_BIT;
		case ShaderStage::TessControl:
			return VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
		case ShaderStage::TessEval:
			return VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;
		case ShaderStage::Geometry:
			return VK_SHADER_STAGE_GEOMETRY_BIT;
		case ShaderStage::Fragment:
			return VK_SHADER_STAGE_FRAGMENT_BIT;
		case ShaderStage::Compute:
			return VK_SHADER_STAGE_COMPUTE_BIT;
		case ShaderStage::Raygen:
			return VK_SHADER_STAGE_RAYGEN_BIT_KHR;
		case ShaderStage::Anyhit:
			return VK_SHADER_STAGE_ANY_HIT_BIT_KHR;
		case ShaderStage::ClosestHit:
			return VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR;
		case ShaderStage::Miss:
			return VK_SHADER_STAGE_MISS_BIT_KHR;
		case ShaderStage::Intersection:
			return VK_SHADER_STAGE_INTERSECTION_BIT_KHR;
		case ShaderStage::Callable:
			return VK_SHADER_STAGE_CALLABLE_BIT_KHR;
		case ShaderStage::Task:
			return VK_SHADER_STAGE_TASK_BIT_EXT;
		case ShaderStage::Mesh:
			return VK_SHADER_STAGE_MESH_BIT_EXT;
		default:
			return VK_SHADER_STAGE_VERTEX_BIT;
		}
	}

	VkPrimitiveTopology VkPipelineUtils::GetVkTopo(PrimitiveTopology topo)
	{
		switch (topo)
		{
		case PrimitiveTopology::PointList:
			return VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
		case PrimitiveTopology::LineList:
			return VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
		case PrimitiveTopology::LineStrip:
			return VK_PRIMITIVE_TOPOLOGY_LINE_STRIP;
		case PrimitiveTopology::TriangleList:
			return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		case PrimitiveTopology::TriangleStrip:
			return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
		case PrimitiveTopology::TriangleFan:
			return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN;
		case PrimitiveTopology::LineListAdj:
			return VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY;
		case PrimitiveTopology::LineStripAdj:
			return VK_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY;
		case PrimitiveTopology::TriangleListAdj:
			return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY;
		case PrimitiveTopology::TriangleStripAdj:
			return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY;
		default:
			return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		}
	}
}
