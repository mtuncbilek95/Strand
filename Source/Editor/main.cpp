#include <QApplication>

#include <Editor/SceneWidget/SceneWidget.h>
#include <Editor/TerminalWidget/TerminalWidget.h>

using namespace Flax;

int main(int argC, char** argV)
{
	QApplication app(argC, argV);

	TerminalWidget t;
	t.show();

	SceneWidget widget;
	widget.show();
	widget.RunScene();

	return app.exec();
}
