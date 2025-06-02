#include "GfxVkQueue.h"

#include <Runtime/Graphics/Vulkan/Device/GfxVkDevice.h>
#include <Runtime/Graphics/Vulkan/Debug/VDebug.h>

namespace Flax
{
	GfxVkQueue::GfxVkQueue(const GfxQueueDesc& desc, GfxDevice* pDevice) : GfxQueue(desc, pDevice), m_queue(VK_NULL_HANDLE)
	{
	}

	GfxVkQueue::~GfxVkQueue()
	{
		VDebug::VkAssert(vkQueueWaitIdle(m_queue), "~GfxVkQueue()");
	}

	void* GfxVkQueue::Queue() const
	{
		return static_cast<void*>(m_queue);
	}

	void GfxVkQueue::WaitIdle() const
	{
		VDebug::VkAssert(vkQueueWaitIdle(m_queue), "~GfxVkQueue()");
	}
}
