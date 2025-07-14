#include "GUIApplication.h"

#include <Runtime/Data/Platform/PlatformPath.h>
#include <Runtime/Data/Config/RuntimeLoader.h>
#include <Runtime/FileSystem/Service/VirtualFileService.h>
#include <Runtime/FileSystem/DiskFile/DiskFileSystem.h>

namespace Flax
{
	GUIApplication::GUIApplication(i32 argC, c8** argV) : QApplication(argC, argV)
	{
		Path engineConfig = Path(PlatformPath::AppDataPath());
		engineConfig /= "Neuvex/FlaxEngine/EngineConfig.toml";
		auto settings = RuntimeLoader::LoadEngineSettings(engineConfig.string());

		auto vfm = RuntimeService::Get<VirtualFileService>();
		vfm->Initialize(R"(D:\Projects\FlaxTestProject)");
		vfm->Mount("Assets", NewRef<DiskFileSystem>());
		vfm->Mount("Caches", NewRef<DiskFileSystem>());
		vfm->Mount("Scripts", NewRef<DiskFileSystem>());
		vfm->Mount("Intermediate", NewRef<DiskFileSystem>());

		// Get first scene via runtime
	}

	GUIApplication::~GUIApplication()
	{
	}
}
