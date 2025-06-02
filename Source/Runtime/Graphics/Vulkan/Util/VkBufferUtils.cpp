#include "VkBufferUtils.h"

#include <magic_enum.hpp>

namespace Flax
{
	VkBufferUsageFlags VkBufferUtils::GetVkBufferUsage(BufferUsage usage)
	{
		VkBufferUsageFlags flags = 0;

		for (auto u : magic_enum::enum_values<BufferUsage>())
		{
			if (HasFlag(usage, u))
			{
				switch (u)
				{
				case BufferUsage::TransferSrc:
					flags |= VK_BUFFER_USAGE_TRANSFER_SRC_BIT; break;
				case BufferUsage::TransferDst:
					flags |= VK_BUFFER_USAGE_TRANSFER_DST_BIT; break;
				case BufferUsage::UniformTexel:
					flags |= VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT; break;
				case BufferUsage::StorageTexel:
					flags |= VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT; break;
				case BufferUsage::Uniform:
					flags |= VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT; break;
				case BufferUsage::Storage:
					flags |= VK_BUFFER_USAGE_STORAGE_BUFFER_BIT; break;
				case BufferUsage::Index:
					flags |= VK_BUFFER_USAGE_INDEX_BUFFER_BIT; break;
				case BufferUsage::Vertex:
					flags |= VK_BUFFER_USAGE_VERTEX_BUFFER_BIT; break;
				case BufferUsage::Indirect:
					flags |= VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT; break;
				case BufferUsage::VideoDecodeSrc:
					flags |= VK_BUFFER_USAGE_VIDEO_DECODE_SRC_BIT_KHR; break;
				case BufferUsage::VideoDecodeDst:
					flags |= VK_BUFFER_USAGE_VIDEO_DECODE_DST_BIT_KHR; break;
				default:
					break;
				}
			}
		}

		return flags;
	}
}
