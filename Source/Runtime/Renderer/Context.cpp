#include "Context.h"

#include <Runtime/Window/BasicWindow.h>

namespace Flax
{
	void Context::CreateContext(BasicWindow* window)
	{
		InstanceProps vkInstProp =
		{
			.appName = "Flax",
			.engineName = "Flax",
			.appVersion = Math::Vec3u(1, 0, 0),
			.engineVersion = Math::Vec3u(1, 0, 0)
		};
		m_vkInstance = NewRef<VInstance>(vkInstProp);
		m_vkDevice = NewRef<VDevice>(DeviceProps(), m_vkInstance.get());
		m_vkGQueue = m_vkDevice->CreateQueue(VK_QUEUE_GRAPHICS_BIT);

		SwapchainProps vkSwapProp =
		{
			.imageSize = { 1280, 720 },
			.imageCount = 3,
			.format = VK_FORMAT_R8G8B8A8_UNORM,
			.presentMode = VK_PRESENT_MODE_FIFO_KHR,
			.graphicsQueue = m_vkGQueue.get(),
			.windowHandler = window->GetHandle()
		};
		m_vkSwapchain = NewRef<VSwapchain>(vkSwapProp, m_vkDevice.get());

		CmdPoolProps vkGPoolProp =
		{
			.queue = m_vkGQueue.get()
		};
		m_vkGPool = NewRef<VCmdPool>(vkGPoolProp, m_vkDevice.get());

		for (usize i = 0; i < m_vkSwapchain->GetImageCount(); i++)
			m_vkGBuffers.push_back(m_vkGPool->CreateCmdBuffer());
		m_vkFence = NewRef<VFence>(false, m_vkDevice.get());

		for (usize i = 0; i < m_vkSwapchain->GetImageCount(); i++)
			m_vkSemaphores.push_back(NewRef<VSemaphore>(m_vkDevice.get()));
	}

	void Context::DestroyContext()
	{
		m_vkDevice->WaitDeviceIdle();

		m_vkSemaphores.clear();
		m_vkFence.reset();
		m_vkGBuffers.clear();
		m_vkGPool.reset();
		m_vkSwapchain.reset();
		m_vkGQueue.reset();
		m_vkDevice.reset();
		m_vkInstance.reset();
	}

	void Context::PrepareFrame()
	{
		m_index = m_vkSwapchain->AcquireNextImage(nullptr, m_vkFence.get());
		m_vkFence->Wait();
		m_vkFence->Reset();

		m_vkGBuffers[m_index]->BeginRecord();
	}

	void Context::SubmitFrame()
	{
		m_vkGBuffers[m_index]->EndRecord();

		m_vkGQueue->Submit({ m_vkGBuffers[m_index].get() }, {}, { m_vkSemaphores[m_index].get() }, nullptr, VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT);
		m_vkSwapchain->Present({ m_vkSemaphores[m_index].get() });
	}
}