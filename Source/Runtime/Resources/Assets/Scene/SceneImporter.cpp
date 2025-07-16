#include "SceneImporter.h"

namespace Flax
{
	void SceneImporter::Import(const Path& virtualPath)
	{
		Log::Info(LogType::Asset, "Importing scene from '{}'", virtualPath.string());
	}
}
