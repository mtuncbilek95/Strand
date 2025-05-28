#include "Application.h"

#include <Runtime/Vulkan/Context/VContext.h>
#include <Runtime/Vulkan/Device/VDevice.h>

#include <Runtime/Resource/Shader/ShaderResource.h>
#include <Runtime/Services/ResourceService.h>

#include <Mesh/Mesh.h>

namespace Flax
{
	Mesh* testMesh;

	Application::Application()
	{
		WindowProps wProp =
		{
			.windowName = "Import Example",
			.windowSize = { 1920, 1080 },
			.windowMode = WindowMode::Windowed,
		};
		m_mainWindow = NewRef<BasicWindow>(wProp);
		WindowContext::Get().SetContextWindow(m_mainWindow);

		m_renderContext = VContext::Get().Initialize();

		testMesh = new Mesh(R"(D:\Projects\Flax\Resources\Sci-fi Helmet\)");
	}

	Application::~Application()
	{
		delete testMesh;
	}

	void Application::Run()
	{
		m_mainWindow->Show();
		while (m_mainWindow->IsActive())
		{
			m_mainWindow->ProcessEvents();

			// Do other stuff
		}

		m_renderContext->Device()->WaitDeviceIdle();
		m_mainWindow->Hide();

		ServiceLocator::ClearServices();
	}
}
