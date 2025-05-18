#include "VFence.h"

#include <Runtime/Vulkan/Debug/VDebug.h>
#include <Runtime/Vulkan/Device/VDevice.h>

namespace Flax
{
	VFence::VFence(b8 signalled, VDevice* pDevice) : VObject(pDevice)
	{
		VkFenceCreateInfo fenceInfo = { VK_STRUCTURE_TYPE_FENCE_CREATE_INFO };
		fenceInfo.flags = signalled ? VK_FENCE_CREATE_SIGNALED_BIT : 0;
		VDebug::VkAssert(vkCreateFence(GetRoot()->GetVkDevice(), &fenceInfo, nullptr, &m_fence), "VFence");
	}

	VFence::~VFence()
	{
        if (m_fence != VK_NULL_HANDLE)
        {
            vkDestroyFence(GetRoot()->GetVkDevice(), m_fence, nullptr);
            m_fence = VK_NULL_HANDLE;
        }
	}

	void VFence::Wait() const
	{
		VDebug::VkAssert(vkWaitForFences(GetRoot()->GetVkDevice(), 1, &m_fence, VK_TRUE, u64_max), "VFence");
	}

	void VFence::Reset() const
	{
		VDebug::VkAssert(vkResetFences(GetRoot()->GetVkDevice(), 1, &m_fence), "VFence");
	}
}