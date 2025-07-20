#include "SceneImporter.h"

#include <Runtime/Resources/Assets/AssetImportRegistry.h>
#include <Runtime/Resources/Assets/Scene/SceneMetadata.h>

namespace Flax
{
	void SceneImporter::Import(const Path& virtualPath)
	{
		Log::Info(LogType::Asset, "Importing scene from '{}'", virtualPath.string());
	}
}
