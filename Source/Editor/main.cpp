#include <Editor/GUIApplication/GUIApplication.h>

#include <Editor/EditorWindow/EditorWindow.h>
#include <Editor/TerminalView/View/TerminalView.h>
#include <Editor/SceneGraph/SceneGraphWidget.h>
#include <Editor/DomainView/DomainViewWidget.h>
#include <Editor/PropertyInspector/PropertyInspectorWidget.h>

#include <Editor/ImportWidget/TextureImportView.h>

#include <Editor/PropertyInspector/PropertyInspectorListView.h>

using namespace Strand;

int main(int argC, char** argV)
{
	GUIApplication app(argC, argV);

	EditorWindow* wind = new EditorWindow();

	wind->addTabTo(TabDirection::Bottom, new DomainViewWidget(), "Content Browser");
	wind->addTabTo(TabDirection::Bottom, new TerminalView(), "Terminal");
	wind->addTabTo(TabDirection::Left, new SceneGraphWidget(), "Scene Graph");
	wind->addTabTo(TabDirection::Right, new PropertyInspectorWidget(), "Property Inspector");

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

class TestClass
{
private:
	[[Reflection::Field]]
	int testField = 0;
};
