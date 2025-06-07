#include "AssetMetadata.h"

#include <Runtime/Resource/Asset/Core/AssetTypeRegistry.h>

#include <magic_enum.hpp>

namespace Flax
{
	void AssetMetadata::Serialize(Json& jsonOut) const
	{
		jsonOut["Uuid"] = assetId.ToString();
		jsonOut["AssetName"] = name;
		jsonOut["AssetType"] = type;
		jsonOut["AssetPath"] = path;

		Json extJson = {};
		if(extension)
			extension->Serialize(extJson);

		jsonOut["Asset Custom Details"] = extJson;
		Log::Debug(LogType::Resource, "{} has been serialized!", name);
	}

	void AssetMetadata::Deserialize(const Json& jsonIn)
	{
		assetId = Uuid(jsonIn["Uuid"]);
		name = jsonIn["AssetName"];
		type = jsonIn["AssetType"].get<String>();
		path = jsonIn["AssetPath"];

		const auto* registry = AssetTypeRegistry::TypeInfo(AssetTypeId::TypeId(type));
		if (jsonIn.contains("Asset Custom Details"))
		{
			const Json& extJson = jsonIn["Asset Custom Details"];

			extension = registry->CreateExtension();
			if (extension)
				extension->Deserialize(extJson);
		}
	}
}
