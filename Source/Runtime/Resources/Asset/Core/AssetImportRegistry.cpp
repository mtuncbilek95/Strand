#include "AssetImportRegistry.h"

namespace Flax
{
	void AssetImportRegistry::RegisterImporter(const String& fileExt, function<Ref<IAssetImporter>()> importer)
	{
		m_importers[fileExt] = importer;
	}

	Ref<IAssetImporter> AssetImportRegistry::Importer(const String& fileExt)
	{
		auto it = m_importers.find(fileExt);
		if (it != m_importers.end())
			return it->second();

		Log::Critical(LogType::Asset, "No importer registered for file extension '{}'.", fileExt);
		return nullptr;
	}
}
