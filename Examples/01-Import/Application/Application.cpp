#include "Application.h"

#include <Runtime/Window/WindowContext.h>
#include <Runtime/Graphics/Context/GfxContext.h>

#include <Runtime/Resources/Asset/Core/AssetImportRegistry.h>

namespace Flax
{
	auto& wCtx = WindowContext::Get();
	auto& gCtx = GfxContext::Get();

	Application::Application(i32 argC, c8** argV)
	{
		WindowProps windProp = WindowProps().setWindowName("Flaxbox")
			.setWindowMode(WindowMode::Windowed)
			.setWindowSize({ 1920, 1080 });
		wCtx.CreateCoreWindow(windProp);

		GfxContextDesc contextDesc = GfxContextDesc().setAPIType(GfxType::Vulkan)
			.setAppName("Flaxbox")
			.setAppVersion({ 1, 0, 0 })
			.setColorFormat(ImageFormat::R8G8B8A8_UNorm)
			.setImageCount(2)
			.setGraphicsQueueCount(1)
			.setComputeQueueCount(1)
			.setTransferQueueCount(1)
			.setDepthFormat(ImageFormat::D32_SFloat)
			.setPresentMode(PresentMode::Fifo);

		gCtx.CreateContext(contextDesc);
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		// TODO: Try to use multi-thread for initializing the scene, Sponza that has been used is quite large
		// Load scene data which will handle the loading of meshes, materials, textures, etc.
		wCtx.CoreWindow()->Show();

		while (wCtx.CoreWindow()->IsActive())
		{
			wCtx.CoreWindow()->ProcessEvents();
			
			gCtx.BeginFrame();
			// Resolve m_scene here. Which will handle rendering the scene
			gCtx.EndFrame();
		}

		gCtx.DestroyContext();
		wCtx.CoreWindow()->Hide();
	}
}
