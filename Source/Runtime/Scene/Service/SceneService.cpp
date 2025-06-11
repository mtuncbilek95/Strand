#include "SceneService.h"

namespace Flax
{
	namespace
	{
		struct SceneServiceRegister
		{
			SceneServiceRegister()
			{
				RuntimeService::Register<SceneService>(NewRef<SceneService>());
			}
		};

		static SceneServiceRegister gbSceneService;
	}

	Ref<Scene> SceneService::LoadSceneFromFile(const String& path)
	{
		return nullptr;
	}
}