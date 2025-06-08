#include "ModelImporter.h"

#include <Runtime/Resources/Asset/Core/AssetRegistrar.h>
#include <Runtime/Resources/Asset/Model/ModelMetadata.h>

namespace Flax
{
	ModelImporter::~ModelImporter()
	{
	}

	u32 ModelImporter::AssetTypeID() const
	{
		return AssetTypeId::Get().TypeId(AssetTypeName());
	}

	void ModelImporter::Import(const String& sourcePath, AssetMetadata& outMetadata)
	{
	}

	static AssetRegistrar modelReg("model", "gltf",
		[]() { return NewRef<ModelImporter>(); },
		[]() { return NewRef<ModelMetadata>(); });

	static AssetRegistrar modelReg2("model", "fbx",
		[]() { return NewRef<ModelImporter>(); },
		[]() { return NewRef<ModelMetadata>(); });
}
