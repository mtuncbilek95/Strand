#include <QApplication>

#include <Editor/Window/EditorWindow.h>
#include <Editor/SceneWidget/SceneWidget.h>

using namespace Flax;

int main(int argC, char** argV)
{
	QApplication app(argC, argV);

	EditorWindow* wnd = new EditorWindow();
	wnd->show();
	wnd->RunEditor();

	return app.exec();
}