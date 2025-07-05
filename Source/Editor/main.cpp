#include <QApplication>

#include <Runtime/Data/Config/ProjectConfig.h>

int main(int argC, char** argV)
{
	QApplication app(argC, argV);

	Flax::ProjectConfig config;
	config.LoadFrom(R"(D:\Projects\FlaxTestProject\TestProject.flax)");
	return app.exec();
}