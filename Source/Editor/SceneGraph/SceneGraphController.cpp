#include "SceneGraphController.h"

namespace Flax
{
	void SceneGraphController::InitializeController()
	{
	}

	void SceneGraphController::ShutdownController()
	{
	}

	void SceneGraphController::onSceneLoadRequested(const QString& filePath)
	{
		Path scenePath = filePath.toStdString();
		if (scenePath.extension().string().substr(1) != "scene")
			return; // Just move on since its not the right file type

		Log::Debug(LogType::Editor, "Scene '{}' has been loaded.", scenePath.stem().string());
		// Call the SceneBuilder to load the scene
	}
}
