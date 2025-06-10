#include <QApplication>

#include <Editor/HierarchyWidget/HierarchyWidget.h>

using namespace Flax;

int main(int argC, char** argV)
{
	QApplication app(argC, argV);

	HierarchyWidget test;
	test.show();

	return app.exec();
}
