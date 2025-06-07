#include "AssetMetadata.h"

#include <magic_enum.hpp>

namespace Flax
{
	void AssetMetadata::Serialize(Json& jsonOut) const
	{
		jsonOut["Uuid"] = assetId.ToString();
		jsonOut["AssetName"] = name;
		jsonOut["AssetType"] = magic_enum::enum_name<AssetType>(type);
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
		type = magic_enum::enum_cast<AssetType>(jsonIn["AssetType"].get<String>()).value_or(AssetType::Unknown);
		path = jsonIn["AssetPath"];

		// TODO: Get extension registry structure
		// const auto* registry = AssetTypeRegistry::Get().GetAssetTypeExtension(GetTypeId(magic_enum::enum_name<AssetType>(type)));
		if (jsonIn.contains("Asset Custom Details"))
		{
			const Json& extJson = jsonIn["Asset Custom Details"];

			// TODO: Create extension instance based on type
			// extension = registry->CreateExtension();
			if (extension)
				extension->Deserialize(extJson);
		}
	}
}
