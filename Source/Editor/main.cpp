#include <QApplication>

#include <Editor/InspectorWidget/TransformWidget.h>

using namespace Flax;

int main(int argC, char** argV)
{
	QApplication app(argC, argV);

	TransformWidget test;
	test.show();

	return app.exec();
}
