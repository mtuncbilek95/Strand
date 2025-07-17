#include "SceneImporter.h"

#include <Runtime/Resources/Assets/AssetImportRegistry.h>

namespace Flax
{
	void SceneImporter::Import(const Path& virtualPath)
	{
		Log::Info(LogType::Asset, "Importing scene from '{}'", virtualPath.string());
	}

	struct SceneImporterRegister
	{
		SceneImporterRegister() { AssetImportRegistry::Get().RegisterImporter<SceneImporter>(); }
	};
	static SceneImporterRegister gb_sceneImporterRegister;
}
