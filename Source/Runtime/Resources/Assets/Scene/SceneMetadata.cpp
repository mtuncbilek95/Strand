#include "SceneMetadata.h"

#include <Runtime/Resources/Assets/AssetMetadataRegistry.h>

namespace Flax
{
	void SceneMetaExtension::Serialize(Toml& tomlOut)
	{
		tomlOut.emplace("SceneName", sceneName);
		tomlOut.emplace("SceneDataPath", sceneDataPath.string());
	}

	void SceneMetaExtension::Deserialize(const Toml& tomlIn)
	{
		sceneName = tomlIn.at("SceneName").as_string()->get();
		sceneDataPath = Path(tomlIn.at("SceneDataPath").as_string()->get());
	}

	struct SceneMetaExtensionRegister
	{
		SceneMetaExtensionRegister() { AssetMetadataRegistry::Get().RegisterMetaExtension<SceneMetaExtension>("scene"); }
	};
	static SceneMetaExtensionRegister gb_sceneMetaExtensionRegister;
}
