#include <Editor/GUIApplication/GUIApplication.h>

#include <Editor/EditorWindow/EditorWindow.h>
#include <Editor/TerminalView/View/TerminalView.h>
#include <Editor/SceneHierarchy/View/SceneHierarchyView.h>
#include <Editor/DomainView/DomainViewWidget.h>

#include <Editor/ImportWidget/TextureImportView.h>

using namespace Flax;

int main(int argC, char** argV)
{
	GUIApplication app(argC, argV);

	EditorWindow* wind = new EditorWindow();

	wind->addTabTo(TabDirection::Bottom, new DomainViewWidget(), "Content Browser");
	wind->addTabTo(TabDirection::Bottom, new TerminalView(), "Terminal");

	wind->show();

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