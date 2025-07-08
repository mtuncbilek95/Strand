#include "GUIApplication.h"

#include <Runtime/Data/Platform/PlatformPath.h>
#include <Runtime/Data/Config/RuntimeLoader.h>

namespace Flax
{
	GUIApplication::GUIApplication(i32 argC, c8** argV) : QApplication(argC, argV)
	{
		Path engineConfig = Path(PlatformPath::AppDataPath());
		engineConfig /= "Neuvex/FlaxEngine/EngineConfig.toml";
		auto settings = RuntimeLoader::LoadEngineSettings(engineConfig.string());
	}

	GUIApplication::~GUIApplication()
	{
	}
}
