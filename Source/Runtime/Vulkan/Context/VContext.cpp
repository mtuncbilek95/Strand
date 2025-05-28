#include "VContext.h"

#include <Runtime/Window/WindowContext.h>

#include <Runtime/Vulkan/Instance/VInstance.h>
#include <Runtime/Vulkan/Device/VDevice.h>
#include <Runtime/Vulkan/Queue/VQueue.h>
#include <Runtime/Vulkan/Swapchain/VSwapchain.h>

namespace Flax
{
	VContext* VContext::Initialize()
	{
		auto* coreWindow = WindowContext::Get().CoreWindow();

		InstanceProps vkInstProp =
		{
			.appName = "Flax",
			.engineName = "Flax",
			.appVersion = Math::Vec3u(1, 0, 0),
			.engineVersion = Math::Vec3u(1, 0, 0)
		};
		m_vInstance = NewRef<VInstance>(vkInstProp);
		m_vDevice = NewRef<VDevice>(DeviceProps(), m_vInstance.get());

		m_vGraphicsQueue = m_vDevice->CreateQueue(VK_QUEUE_GRAPHICS_BIT);
		m_vTransferQueue = m_vDevice->CreateQueue(VK_QUEUE_TRANSFER_BIT);
		m_vComputeQueue = m_vDevice->CreateQueue(VK_QUEUE_COMPUTE_BIT);

		SwapchainProps vkSwapProp =
		{
			.imageSize = coreWindow->GetSize(),
			.imageCount = 2,
			.format = VK_FORMAT_R8G8B8A8_UNORM,
			.presentMode = VK_PRESENT_MODE_FIFO_KHR,
			.graphicsQueue = m_vGraphicsQueue.get(),
			.windowHandler = coreWindow->GetHandle()
		};

		m_vSwapchain = NewRef<VSwapchain>(vkSwapProp, m_vDevice.get());

		return this;
	}

	void VContext::Destroy()
	{
		m_vDevice->WaitDeviceIdle();

		m_vSwapchain.reset();
		m_vDevice.reset();
		m_vInstance.reset();
	}
}
