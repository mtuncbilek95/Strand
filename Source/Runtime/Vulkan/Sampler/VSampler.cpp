#include "VSampler.h"

#include <Runtime/Vulkan/Debug/VDebug.h>
#include <Runtime/Vulkan/Device/VDevice.h>

namespace Flax
{
	VSampler::VSampler(const SamplerProps& desc, VDevice* pDevice) : VObject(pDevice), m_props(desc)
	{
		VkSamplerCreateInfo info = { VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO };
		info.magFilter = desc.magFilter;
		info.minFilter = desc.minFilter;
		info.mipmapMode = desc.mipmapMode;
		info.addressModeU = desc.addressModeU;
		info.addressModeV = desc.addressModeV;
		info.addressModeW = desc.addressModeW;
		info.mipLodBias = desc.mipLodBias;
		info.anisotropyEnable = desc.anisotropyEnable ? VK_TRUE : VK_FALSE;
		info.maxAnisotropy = desc.maxAnisotropy;
		info.compareEnable = desc.compareEnable ? VK_TRUE : VK_FALSE;
		info.compareOp = desc.compareOp;
		info.minLod = desc.minLod;
		info.maxLod = desc.maxLod;
		info.borderColor = desc.borderColor;
		info.unnormalizedCoordinates = VK_FALSE;

		VDebug::VkAssert(vkCreateSampler(GetRoot()->GetVkDevice(), &info, nullptr, &m_sampler), "VSampler");
	}

	VSampler::~VSampler()
	{
        if (m_sampler != VK_NULL_HANDLE)
        {
            vkDestroySampler(GetRoot()->GetVkDevice(), m_sampler, nullptr);
            m_sampler = VK_NULL_HANDLE;
        }
	}
}