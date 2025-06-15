#include "GfxContext.h"

#include <Runtime/Window/WindowContext.h>

#include <Runtime/Graphics/Vulkan/Instance/GfxVkInstance.h>

#include <Runtime/Graphics/RHI/Device/GfxDevice.h>
#include <Runtime/Graphics/RHI/Queue/GfxQueue.h>
#include <Runtime/Graphics/RHI/Image/GfxImage.h>
#include <Runtime/Graphics/RHI/Image/GfxImageView.h>
#include <Runtime/Graphics/RHI/Swapchain/GfxSwapchain.h>
#include <Runtime/Graphics/RHI/Command/GfxCommandPool.h>
#include <Runtime/Graphics/RHI/Command/GfxCommandBuffer.h>
#include <Runtime/Graphics/RHI/Sync/GfxSemaphore.h>
#include <Runtime/Graphics/RHI/Sync/GfxFence.h>

namespace Flax
{
	static Ref<GfxInstance> RegisterGfxInstance(const GfxInstanceDesc& desc)
	{
		switch (desc.type)
		{
		case GfxType::Vulkan:
			return NewRef<GfxVkInstance>(desc);
		case GfxType::None:
		default:
			Log::Critical(LogType::GfxContext, "Could not find the proper API to start!");
			return nullptr;
		}
	}

	void GfxContext::CreateContext(const GfxContextDesc& desc)
	{
		GfxInstanceDesc instDesc = GfxInstanceDesc().setAPIType(desc.type)
			.setAppName(desc.appName)
			.setAppVersion(desc.appVer);
		m_instance = RegisterGfxInstance(instDesc);

		GfxDeviceDesc devDesc = GfxDeviceDesc().setGraphicsQueueCount(desc.graphicsQueueCount)
			.setComputeQueueCount(desc.computeQueueCount)
			.setTransferQueueCount(desc.transferQueueCount);
		m_device = m_instance->CreateDevice(devDesc);

		m_graphicsQueue = m_device->CreateQueue(QueueType::Graphics);
		m_transferQueue = m_device->CreateQueue(QueueType::Transfer);
		m_computeQueue = m_device->CreateQueue(QueueType::Compute);

		GfxSwapchainDesc swapDesc = GfxSwapchainDesc().setFormat(desc.colorFormat)
			.setGraphicsQueue(m_graphicsQueue.get())
			.setImageCount(desc.imageCount)
			.setImageSize(desc.windowSize)
			.setPresentMode(desc.presentMode)
			.setWindowHandler(desc.windowHandle);

		m_swapchain = m_device->CreateSwapchain(swapDesc);

		GfxCommandPoolDesc poolDesc = GfxCommandPoolDesc().setQueue(m_graphicsQueue.get())
			.setFlags(CommandPoolFlags::ResetCommandBuffer);
		m_cmdPool = m_device->CreateCommandPool(poolDesc);

		m_cmdBuffers.resize(swapDesc.imageCount);
		m_signalSems.resize(swapDesc.imageCount);
		m_waitSems.resize(swapDesc.imageCount);
		m_fences.resize(swapDesc.imageCount);
		for (usize i = 0; i < swapDesc.imageCount; i++)
		{
			m_cmdBuffers[i] = m_cmdPool->CreateBuffer(CommandLevel::Primary);
			m_signalSems[i] = m_device->CreateSyncSemaphore(GfxSemaphoreDesc());
			m_waitSems[i] = m_device->CreateSyncSemaphore(GfxSemaphoreDesc());
			m_fences[i] = m_device->CreateSyncFence(GfxFenceDesc().setSignal(false));
		}
	}

	void GfxContext::DestroyContext()
	{
		m_device->WaitIdle();

		m_fences.clear();
		m_waitSems.clear();
		m_signalSems.clear();
		m_cmdBuffers.clear();
	}

	void GfxContext::BeginFrame()
	{
		if (!m_frameCompleted)
			return;

		m_frameCompleted = false;

		m_currIndex = m_swapchain->AcquireNextImage(m_waitSems[m_prevIndex].get(), nullptr);
		m_cmdBuffers[m_currIndex]->BeginRecord();
	}

	void GfxContext::EndFrame()
	{
		m_cmdBuffers[m_currIndex]->EndRecord();

		m_graphicsQueue->Submit({ m_cmdBuffers[m_currIndex].get() }, { m_waitSems[m_prevIndex].get() },
			{ m_signalSems[m_currIndex].get() }, m_fences[m_currIndex].get(), PipelineStageFlags::ColorAttachment);
		
		m_swapchain->Present({ m_signalSems[m_currIndex].get() });
		m_fences[m_currIndex]->WaitIdle();
		m_fences[m_currIndex]->Reset();

		m_prevIndex = m_currIndex;
		m_frameCompleted = true;
	}

	void GfxContext::DispatchResize(const Math::Vec2u& newSize)
	{
		m_device->WaitIdle();
		m_swapchain->Resize(newSize);

		Log::Debug(LogType::GfxContext, "Resized as '{0} x {1}'", newSize.x, newSize.y);
	}
}
