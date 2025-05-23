#include "SceneManager.h"

namespace Flax
{
	namespace
	{
		struct SceneManagerRegister
		{
			SceneManagerRegister()
			{
				ServiceLocator::Register<SceneManager>(NewRef<SceneManager>());
			}
		};

		static SceneManagerRegister sceneManager;
	}
}
