#include "AssetRegistrar.h"

namespace Flax
{
	AssetRegistrar::AssetRegistrar(const String& typeName, const String& extName, function<Ref<IAssetImporter>()> importerFactory, 
		function<Ref<IAssetMetadataExtension>()> metadataFactory)
	{
		u32 id = AssetTypeId::Get().TypeId(typeName);

		AssetTypeInfo info;
		info.infoId = id;
		info.name = typeName;
		info.CreateExtension = metadataFactory;
		info.CreateImporter = importerFactory;

		AssetTypeRegistry::Get().RegisterType(info.name, info);
		AssetImportRegistry::Get().RegisterImporter(extName, info.CreateImporter);

		Log::Debug(LogType::Asset, "Registered asset type: {0} ({1})", info.name, extName);
	}
}
