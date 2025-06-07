#include "AssetImportRegistry.h"

namespace Flax
{
	static HashMap<String, function<Ref<IAssetImporter>()>> importers;

	void AssetImportRegistry::RegisterImporter(const String& fileExt, function<Ref<IAssetImporter>()> importer)
	{
		importers[fileExt] = importer;
	}

	Ref<IAssetImporter> AssetImportRegistry::Importer(const String& fileExt)
	{
		auto it = importers.find(fileExt);
		if (it != importers.end())
			return it->second();

		Log::Critical(LogType::Asset, "No importer registered for file extension '{}'.", fileExt);
		return nullptr;
	}
}
