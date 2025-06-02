#include "GfxContext.h"

#include <Runtime/Window/WindowContext.h>

#include <Runtime/Graphics/Vulkan/Instance/GfxVkInstance.h>

#include <Runtime/Graphics/RHI/Device/GfxDevice.h>
#include <Runtime/Graphics/RHI/Queue/GfxQueue.h>
#include <Runtime/Graphics/RHI/Image/GfxImage.h>
#include <Runtime/Graphics/RHI/Image/GfxImageView.h>
#include <Runtime/Graphics/RHI/Swapchain/GfxSwapchain.h>

#include <Runtime/Graphics/RHI/Shader/GfxShader.h>
#include <Runtime/ShaderCompiler/ShaderCompiler.h>

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
			.setImageSize(WindowContext::Get().CoreWindow()->GetSize())
			.setPresentMode(desc.presentMode)
			.setWindowHandler(WindowContext::Get().CoreWindow()->GetHandle());

		m_swapchain = m_device->CreateSwapchain(swapDesc);

		GfxShaderDesc sDesc = GfxShaderDesc()
			.setByteCode(ShaderCompiler::CompileShader(R"(D:\Projects\Flax\Shaders\ProceduralSky.vert)"))
			.setStage(ShaderStage::Vertex);

		auto shader = m_device->CreateShader(sDesc);
	}
}
