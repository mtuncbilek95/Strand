#include <Runtime/Window/WindowContext.h>
#include <Runtime/DX11/Instance/DXInstance.h>
#include <Runtime/DX11/Device/DXDevice.h>
#include <Runtime/DX11/Swapchain/DXSwapchain.h>
#include <Runtime/DX11/RenderTarget/DXRenderTarget.h>
#include <Runtime/DX11/RenderTarget/DXDepthTarget.h>
#include <Runtime/DX11/Shader/DXShader.h>
#include <Runtime/DX11/Buffer/DXBuffer.h>

#include <Runtime/Input/InputDispatcher.h>

#include "OrbitCamera.h"

struct CBuffer
{
	Math::Mat4f view;
	Math::Mat4f proj;
	Math::Mat4f invView;
	Math::Mat4f invProj;
};

CBuffer camDetails;

using namespace Flax;
using namespace Flax::FlagUtil;

int main()
{
	OrbitCamera mainCamera;
	Math::Vec2i lastPos;

	ServiceLocator::Get<InputDispatcher>()->RegisterListener(WindowPollEvent::MousePressed, [&](const InputEvent& event)
		{
			if (HasFlag(event.payload.mouseButton, MouseButton::Right))
				lastPos = { event.payload.mouseX , event.payload.mouseY };
		});

	ServiceLocator::Get<InputDispatcher>()->RegisterListener(WindowPollEvent::MouseMoved, [&](const InputEvent& event)
		{
			if (IsSameFlag(event.payload.mouseButton, MouseButton::Right))
			{
				Math::Vec2i currentMousePosition = { event.payload.mouseX, event.payload.mouseY };

				i32 deltaX = currentMousePosition[0] - lastPos[0];
				i32 deltaY = currentMousePosition[1] - lastPos[1];

				f32 sensitivity = 0.5f;
				f32 azimuth = deltaX * sensitivity;
				f32 elevation = deltaY * sensitivity;

				mainCamera.SetAzimuth(azimuth);
				mainCamera.SetElevation(elevation);
			}

			if (IsSameFlag(event.payload.mouseButton, MouseButton::Middle))
			{
				Math::Vec2i delta = { event.payload.mouseX, event.payload.mouseY };

				f32 offsetX = static_cast<f32>(delta[0]) - lastPos[0];
				f32 offsetY = static_cast<f32>(delta[1]) - lastPos[1];

				auto zoomRatio = mainCamera.GetDistance();
				auto sensitivity = 0.0001 * zoomRatio;
				offsetX *= sensitivity;
				offsetY *= sensitivity;
				mainCamera.Dolly({ -offsetX, -offsetY });
			}

			lastPos = { event.payload.mouseX , event.payload.mouseY };
		});

	ServiceLocator::Get<InputDispatcher>()->RegisterListener(WindowPollEvent::MouseScrolled, [&](const InputEvent& event)
		{
			if (HasFlag(event.payload.mouseButton, MouseButton::Right))
			{
				f32 scrollDelta = event.payload.scrollDelta;
				f32 scrollSensitivity = .1f;
				mainCamera.SetDistance(-scrollDelta * scrollSensitivity);
			}
		});

	WindowProps windProps =
	{
		.windowName = "Flaxbox",
		.windowSize = { 1920, 1080 },
		.windowMode = WindowMode::Windowed,
	};
	auto window = NewRef<BasicWindow>(windProps);
	WindowContext::Get().SetContextWindow(window);

	DXInstance inst;
	DXDevice device(&inst);
	DXSwapchain swapchain(&device);
	DXRenderTarget rtv(&swapchain, &device);
	DXDepthTarget dsv(DepthTargetProps(), &device);

	ShaderProps vProp =
	{
		.path = R"(D:\Projects\Flax\Shaders\ProceduralSky_Vert.hlsl)",
		.type = ShaderType::Vertex,
		.entry = "VSMain",
		.model = "vs_5_0"
	};
	DXShader vShader(vProp, &device);

	ShaderProps pProp =
	{
		.path = R"(D:\Projects\Flax\Shaders\ProceduralSky_Frag.hlsl)",
		.type = ShaderType::Fragment,
		.entry = "PSMain",
		.model = "ps_5_0"
	};
	DXShader pShader(pProp, &device);

	BufferProps cProp =
	{
		.wholeSize = sizeof(camDetails),
		.stride = sizeof(Math::Mat4f),
		.usage = D3D11_USAGE_DYNAMIC,
		.bindFlags = D3D11_BIND_CONSTANT_BUFFER,
		.cpuAccessFlags = D3D11_CPU_ACCESS_WRITE,
		.miscFlags = 0,
	};
	DXBuffer cBuffer(cProp, &device);
	cBuffer.Update(&camDetails, sizeof(CBuffer));

	window->Show();
	while (window->IsActive())
	{
		window->ProcessEvents();

		camDetails.view = mainCamera.GetViewMatrix();
		camDetails.proj = mainCamera.GetProjectionMatrix();
		camDetails.invView = Math::inverse(mainCamera.GetViewMatrix());
		camDetails.invProj = Math::inverse(mainCamera.GetProjectionMatrix());

		cBuffer.Update(&camDetails, sizeof(CBuffer));

		float clearColor[4] = { 0.4f, 0.3f, 0.2f, 1.0f };
		device.Context()->ClearRenderTargetView(rtv.RTV(), clearColor);
		device.Context()->ClearDepthStencilView(dsv.DSV(), D3D11_CLEAR_DEPTH, 1.0f, 0);

		device.Context()->OMSetRenderTargets(1, rtv.RTVPtr(), dsv.DSV());

		device.Context()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		device.Context()->IASetInputLayout(nullptr);

		device.Context()->VSSetShader(vShader.Vertex(), nullptr, 0);
		device.Context()->PSSetShader(pShader.Pixel(), nullptr, 0);
		device.Context()->VSSetConstantBuffers(0, 1, cBuffer.BufferPtr());

		D3D11_VIEWPORT viewport = {};
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;
		viewport.Width = static_cast<float>(1920);
		viewport.Height = static_cast<float>(1080);
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		device.Context()->RSSetViewports(1, &viewport);

		device.Context()->Draw(6, 0);

		swapchain.Present(1, 0);
	}
}