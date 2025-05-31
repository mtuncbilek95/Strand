#include <Runtime/Window/WindowContext.h>
#include <Runtime/DX11/Instance/DXInstance.h>
#include <Runtime/DX11/Device/DXDevice.h>
#include <Runtime/DX11/Swapchain/DXSwapchain.h>
#include <Runtime/DX11/RenderTarget/DXRenderTarget.h>
#include <Runtime/DX11/RenderTarget/DXDepthTarget.h>

int main()
{
	Flax::WindowProps windProps =
	{
		.windowName = "Flaxbox",
		.windowSize = { 1920, 1080 },
		.windowMode = Flax::WindowMode::Windowed,
	};
	auto window = NewRef<Flax::BasicWindow>(windProps);
	Flax::WindowContext::Get().SetContextWindow(window);

	Flax::DXInstance inst;
	Flax::DXDevice device(&inst);
	Flax::DXSwapchain swapchain(&device);
	Flax::DXRenderTarget rtv(&swapchain, &device);
	Flax::DXDepthTarget dsv(Flax::DepthTargetProps(), &device);

	window->Show();
	while (window->IsActive())
	{
		window->ProcessEvents();

		float clearColor[4] = { 0.4f, 0.3f, 0.2f, 1.0f };
		device.Context()->ClearRenderTargetView(rtv.RTV(), clearColor);
		device.Context()->ClearDepthStencilView(dsv.DSV(), 0, 1.0f, 0);

		device.Context()->OMSetRenderTargets(1, rtv.RTVPtr(), dsv.DSV());

		swapchain.Present(1, 0);
	}
}