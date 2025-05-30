#include "Application.h"

#include <Runtime/Window/WindowContext.h>
#include <Runtime/Graphics/Context/FvkContext.h>
#include <Runtime/Graphics/Pipeline/ProceduralSkyPipeline.h>
#include <Runtime/Graphics/RenderPass/SkyPass.h>

namespace Flax
{
	Application::Application()
	{
		WindowProps windProp =
		{
			.windowName = "Flaxbox",
			.windowSize = { 1920, 1080 },
			.windowMode = WindowMode::Windowed
		};
		m_mainWindow = NewRef<BasicWindow>(windProp);
		WindowContext::Get().SetContextWindow(m_mainWindow);

		FvkContext::Get().CreateContext();

		m_skyPass = NewRef<SkyPass>();

		ProceduralSkyCreateInfo info =
		{
			.vPath = R"(D:\Projects\Flax\Shaders\ProceduralSky.vert)",
			.fPath = R"(D:\Projects\Flax\Shaders\ProceduralSky.frag)",
			.pass = m_skyPass.get()
		};
		m_skyPipeline = NewRef<ProceduralSkyPipeline>(info);
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		m_mainWindow->Show();

		while (m_mainWindow->IsActive())
		{
			m_mainWindow->ProcessEvents();
		}

		m_mainWindow->Hide();
	}
}
