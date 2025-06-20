#include "TextureImporter.h"

#include <Runtime/Resources/Asset/Core/ImporterRegistry.h>
#include <Runtime/Resources/Asset/Texture/TextureMetadata.h>

#include <stb_image.h>

namespace Flax
{
	u32 TextureImporter::AssetTypeId() const
	{
		return 0;
	}

	void TextureImporter::Import(const String& path, AssetMetadata& outMeta)
	{
		Log::Warn(LogType::Asset, "Importing from '{}'", path);

		if (StringHelpers::FileExtension(path).compare(".png") != 0)
		{
			Log::Error(LogType::Asset, "Unsupported file extension '{}'", StringHelpers::FileExtension(path));
			return;
		}

		auto tt = dynamic_cast<TextureMetadata*>(&outMeta);

		i32 x, y, channel;
		stbi_uc* data = stbi_load(path.data(), &x, &y, &channel, STBI_rgb_alpha);
		if (!data)
		{
			Log::Error(LogType::Asset, "Data is invalid!");
			tt->validate = AssetValidation::Invalid;
		}

		tt->assetId = UuidHelper::GenerateID();
		tt->assetName = StringHelpers::NameWithoutExt(path);
		tt->textureSize = { u32(x), u32(y), 1 };
		
		stbi_image_free(data);
	}

	namespace
	{
		struct TexImporterRegister
		{
			TexImporterRegister() { ImporterRegistry::Get().RegisterImporter<TextureImporter>("png"); }
		};

		static TexImporterRegister texImportRegistered;
	}
}
