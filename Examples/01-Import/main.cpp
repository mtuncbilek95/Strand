#include <Runtime/Window/WindowContext.h>
#include <Runtime/Graphics/Context/GfxContext.h>

using namespace Flax;

int main()
{
	WindowProps windProp = WindowProps().setWindowName("Flaxbox")
		.setWindowMode(WindowMode::Windowed)
		.setWindowSize({ 1920, 1080 });
	WindowContext::Get().CreateCoreWindow(windProp);

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

	GfxContext::Get().CreateContext(contextDesc);

	WindowContext::Get().CoreWindow()->Show();

	while (WindowContext::Get().CoreWindow()->IsActive())
	{
		WindowContext::Get().CoreWindow()->ProcessEvents();
	}

	WindowContext::Get().CoreWindow()->Hide();
}