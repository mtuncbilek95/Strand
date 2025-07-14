#include "AssetMetadata.h"

namespace Flax
{
	void AssetMetadata::Serialize(Toml& tomlOut) const
	{
		tomlOut.emplace("AssetMetadata", Toml{
			{"Description", Toml{
				{"AssetGuid", assetGuid.ToString()},
				{"AssetName", assetName},
				{"AssetType", assetType},
				{"VirtualPath", assetPath.string()},
				{"AssetSize", i64(assetSize)},
				{"LastModifiedDate", lastModifiedDate.ToString()}
			}}
			});

		Toml extension;
		metaExtension->Serialize(extension);
		tomlOut["AssetMetadata"].as_table()->emplace("Extension", std::move(extension));
	}

	void AssetMetadata::Deserialize(const Toml& tomlIn)
	{
		Toml tbl = tomlIn;
		Toml& description = *tbl["AssetMetadata"]["Description"].as_table();
		Toml& extension = *tbl["AssetMetadata"]["Extension"].as_table();

		assetGuid = Uuid(description["AssetGuid"].value<String>().value());
		assetName = description["AssetName"].value<String>().value();
		assetType = description["AssetType"].value<String>().value();
		assetPath = Path(description["VirtualPath"].value<String>().value());
		assetSize = description["AssetSize"].value<usize>().value();
		lastModifiedDate = DateTime(description["LastModifiedDate"].value<String>().value());

		metaExtension->Deserialize(extension);
	}
}