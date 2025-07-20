#include "GUIApplication.h"

#include <Runtime/Data/Platform/PlatformPath.h>
#include <Runtime/Data/Config/RuntimeLoader.h>
#include <Runtime/FileSystem/Service/VirtualFileService.h>
#include <Runtime/FileSystem/DiskFile/DiskFileSystem.h>

#include <Editor/Style/StyleManager.h>

namespace Flax
{
	GUIApplication::GUIApplication(i32 argC, c8** argV) : QApplication(argC, argV)
	{
		if (argC <= 1)
		{
			Log::Warn(LogType::Application, "Editor Application has no project to run! Closing the app...");
			//std::exit(-1);
		}

		QStringList families = StyleManager::Get().LoadFontFamilies();
		if (!families.isEmpty())
		{
			QFont font(families.first(), 12);
			//setFont(font);
		}
		setStyleSheet(StyleManager::Get().LoadStyle());

		RuntimeService::InitializeServices();
		auto vfm = RuntimeService::Get<VirtualFileService>();
		// TODO: Path below needs to come from argV, but if not, it should use temporary project in engine.
		vfm->Initialize(R"(D:\Projects\FlaxTestProject)");
		vfm->Mount("Assets", NewRef<DiskFileSystem>());
		vfm->Mount("Caches", NewRef<DiskFileSystem>());
		vfm->Mount("Intermediate", NewRef<DiskFileSystem>());

		Path engineConfig = Path(PlatformPath::AppDataPath());
		engineConfig /= "Neuvex/FlaxRuntime/EngineConfig.toml";
		auto engineSettings = RuntimeLoader::LoadEngineSettings(engineConfig.string());

		auto projectSettings = RuntimeLoader::LoadProjectSettings("/Caches/ProjectSettings.toml");
		/*
			1 - Check arguments to see if we have project to run
				If have, check cache to see if there is a defaultProjectSettings. 
				If not, warn and create one with defaultConfigs we have.
				Those include:
					- Creating Assets, Caches, Scripts and Intermediate folders if there isn't.
					- Check if %AppData%/Roaming/ has Neuvex/FlaxRuntime/EngineConfig.toml
			
			2 - After this, Mount folders and load both engine + project configs.
			3 - Load scene and project browser via settings above.
			4 - Here, at some point, we will start making multi-thread or single-thread dll injections 
			for plugin systems.
			5 - There won't be a layout/QSettings for a long time. But QSettings will be used
			for importing the configFiles.
		*/
	}

	GUIApplication::~GUIApplication()
	{
	}
}
