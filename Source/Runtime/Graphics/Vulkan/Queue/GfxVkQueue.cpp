#include "GfxVkQueue.h"

#include <Runtime/Graphics/Vulkan/Device/GfxVkDevice.h>
#include <Runtime/Graphics/Vulkan/Debug/VDebug.h>
#include <Runtime/Graphics/Vulkan/Command/GfxVkCommandBuffer.h>
#include <Runtime/Graphics/Vulkan/Sync/GfxVkFence.h>
#include <Runtime/Graphics/Vulkan/Sync/GfxVkSemaphore.h>
#include <Runtime/Graphics/Vulkan/Util/VkPipelineUtils.h>

namespace Flax
{
	GfxVkQueue::GfxVkQueue(const GfxQueueDesc& desc, GfxDevice* pDevice) : GfxQueue(desc, pDevice), m_queue(VK_NULL_HANDLE)
	{
	}

	GfxVkQueue::~GfxVkQueue()
	{
		VDebug::VkAssert(vkQueueWaitIdle(m_queue), "~GfxVkQueue");
	}

	void* GfxVkQueue::Queue() const
	{
		return static_cast<void*>(m_queue);
	}

	void GfxVkQueue::Submit(const Vector<GfxCommandBuffer*>& cmdBuffers, const Vector<GfxSemaphore*>& waits, const Vector<GfxSemaphore*>& signals, 
		const GfxFence* fence, PipelineStageFlags flags) const
	{
		Vector<VkCommandBuffer> buffers(cmdBuffers.size());
		Vector<VkSemaphore> waitSems(waits.size());
		Vector<VkSemaphore> signalSems(signals.size());

		for (u32 i = 0; i < cmdBuffers.size(); i++)
			buffers[i] = VkCommandBuffer(cmdBuffers[i]->Buffer());

		for (u32 i = 0; i < waitSems.size(); i++)
			waitSems[i] = VkSemaphore(waits[i]->Semaphore());

		for (u32 i = 0; i < signalSems.size(); i++)
			signalSems[i] = VkSemaphore(signals[i]->Semaphore());

		VkPipelineStageFlags stgFlags = VkPipelineUtils::GetVkStageFlags(flags);

		VkSubmitInfo submitInfo = { VK_STRUCTURE_TYPE_SUBMIT_INFO };
		submitInfo.waitSemaphoreCount = waitSems.size();
		submitInfo.pWaitSemaphores = waitSems.data();
		submitInfo.pWaitDstStageMask = &stgFlags;
		submitInfo.commandBufferCount = buffers.size();
		submitInfo.pCommandBuffers = buffers.data();
		submitInfo.signalSemaphoreCount = signalSems.size();
		submitInfo.pSignalSemaphores = signalSems.data();

		VDebug::VkAssert(vkQueueSubmit(m_queue, 1, &submitInfo, fence ? VkFence(fence->Fence()) : VK_NULL_HANDLE), "GfxVkQueue::Submit");
	}

	void GfxVkQueue::WaitIdle() const
	{
		VDebug::VkAssert(vkQueueWaitIdle(m_queue), "GfxVkQueue::WaitIdle");
	}
}
