#include "AssetRegistrar.h"

namespace Flax
{
	AssetRegistrar::AssetRegistrar(const String& extName, function<Ref<IAssetImporter>()> importerFactory, 
		function<Ref<IAssetMetadataExtension>()> metadataFactory)
	{
		auto importer = importerFactory();
		u32 importerId = AssetTypeId::TypeId(importer->AssetTypeName());

		AssetTypeInfo info;
		info.infoId = importerId;
		info.name = importer->AssetTypeName();
		info.CreateExtension = metadataFactory;
		info.CreateImporter = importerFactory;

		AssetTypeRegistry::RegisterType(info.name, info);
		AssetImportRegistry::RegisterImporter(extName, info.CreateImporter);
	}
}
