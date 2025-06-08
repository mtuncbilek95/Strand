#include "SceneImporter.h"

#include <Runtime/Resources/Asset/Core/AssetRegistrar.h>
#include <Runtime/Resources/Asset/Scene/SceneMetadata.h>

namespace Flax
{
	SceneImporter::~SceneImporter()
	{
	}

	u32 SceneImporter::AssetTypeID() const
	{
		return AssetTypeId::Get().TypeId(AssetTypeName());
	}

	void SceneImporter::Import(const String& sourcePath, AssetMetadata& outMetadata)
	{
	}

	static AssetRegistrar modelReg("scene", "usd",
		[]() { return NewRef<SceneImporter>(); },
		[]() { return NewRef<SceneMetadata>(); });
}
