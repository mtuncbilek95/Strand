#include "SceneService.h"

namespace Flax
{
	namespace
	{
		struct SceneServiceRegister
		{
			SceneServiceRegister()
			{
				ServiceLocator::Register<SceneService>(NewRef<SceneService>());
			}
		};

		static SceneServiceRegister gbSceneService;
	}
}