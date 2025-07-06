#include <QApplication>

#include <Runtime/Data/Config/RuntimeLoader.h>
#include <Runtime/Graphics/Context/GfxContext.h>
#include <Runtime/Data/Platform/PlatformPath.h>

using namespace Flax;

int main(int argC, char** argV)
{
	QApplication app(argC, argV);

	Path engineConfig = Path(PlatformPath::AppDataPath());
	engineConfig /= "Neuvex/FlaxEngine/EngineConfig.toml";
	auto settings = RuntimeLoader::LoadEngineSettings(engineConfig.string());

	//auto ctxDesc = GfxContextDesc().setAPIType(GfxType(settings.graphics.graphicsAPI))
	//	.setAppName(settings.general.engineName)
	//	.setAppVersion({ 1, 0, 0 })
	//	.setColorFormat(ImageFormat(settings.graphics.swapFormat))
	//	.setImageCount(settings.graphics.imageCount)
	//	.setGraphicsQueueCount(1)
	//	.setComputeQueueCount(1)
	//	.setTransferQueueCount(1)
	//	.setDepthFormat(ImageFormat(settings.graphics.depthFormat))
	//	.setPresentMode(PresentMode(settings.graphics.presentMode))
	//	.setWindowSize({ u32(1920), u32(1080) })
	//	.setWindowHandle(nullptr);

	//GfxContext::Get().CreateContext(ctxDesc);

	return app.exec();
}