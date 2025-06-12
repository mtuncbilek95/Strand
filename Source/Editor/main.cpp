#include <QApplication>

#include <Editor/TerminalWidget/TerminalWidget.h>
#include <Editor/HierarchyWidget/HierarchyWidget.h>

using namespace Flax;

int main(int argC, char** argV)
{
	QApplication app(argC, argV);

	HierarchyWidget test;
	test.show();

	return app.exec();
}
