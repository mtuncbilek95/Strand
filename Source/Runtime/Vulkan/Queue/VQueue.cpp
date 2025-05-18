#include "VQueue.h"

#include <Runtime/Vulkan/Debug/VDebug.h>
#include <Runtime/Vulkan/Device/VDevice.h>
#include <Runtime/Vulkan/Sync/VFence.h>
#include <Runtime/Vulkan/Sync/VSemaphore.h>
#include <Runtime/Vulkan/Command/VCmdBuffer.h>

namespace Flax
{
	static String GetQName(VkQueueFlags flags)
	{
		if (flags & VK_QUEUE_GRAPHICS_BIT)
			return "VGraphicsQueue";
		else if (flags & VK_QUEUE_COMPUTE_BIT)
			return "VComputeQueue";
		else if (flags & VK_QUEUE_TRANSFER_BIT)
			return "VTransferQueue";
		else if (flags & VK_QUEUE_SPARSE_BINDING_BIT)
			return "VSparseQueue";
		else
			return "UnknownQueueType";
	}

	VQueue::VQueue(const QueueProps& desc, VDevice* pDevice) : VObject(pDevice), m_props(desc)
	{
	}

	VQueue::~VQueue()
	{
	}

	void VQueue::WaitQueueIdle() const
	{
		VDebug::VkAssert(vkQueueWaitIdle(m_props.queue), GetQName(m_props.flags));
	}

	void VQueue::Submit(const Vector<VCmdBuffer*>& cmds, const Vector<VSemaphore*>& waits, const Vector<VSemaphore*>& signals, VFence* fence, VkPipelineStageFlags flags) const
	{
		Vector<VkCommandBuffer> cmdBuffers(cmds.size());
		Vector<VkSemaphore> waitSems(waits.size());
		Vector<VkSemaphore> signalSems(signals.size());

		for (u32 i = 0; i < cmdBuffers.size(); i++)
			cmdBuffers[i] = cmds[i]->GetVkCmdBuffer();

		for (u32 i = 0; i < waitSems.size(); i++)
			waitSems[i] = waits[i]->GetVkSemaphore();

		for (u32 i = 0; i < signalSems.size(); i++)
			signalSems[i] = signals[i]->GetVkSemaphore();

		VkSubmitInfo submitInfo = {};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.waitSemaphoreCount = waitSems.size();
		submitInfo.pWaitSemaphores = waitSems.data();
		submitInfo.pWaitDstStageMask = &flags;
		submitInfo.commandBufferCount = cmdBuffers.size();
		submitInfo.pCommandBuffers = cmdBuffers.data();
		submitInfo.signalSemaphoreCount = signalSems.size();
		submitInfo.pSignalSemaphores = signalSems.data();

		VDebug::VkAssert(vkQueueSubmit(m_props.queue, 1, &submitInfo, fence ? fence->GetVkFence() : VK_NULL_HANDLE), GetQName(m_props.flags));
	}
}