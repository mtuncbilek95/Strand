#include "TextureImporter.h"

#include <Runtime/Resource/Asset/Core/AssetRegistrar.h>
#include <Runtime/Resource/Asset/Texture/TextureMetadata.h>

namespace Flax
{
	TextureImporter::~TextureImporter()
	{
	}

	u32 TextureImporter::AssetTypeID() const
	{
		return AssetTypeId::TypeId(AssetTypeName());
	}

	void TextureImporter::Import(const String& sourcePath, AssetMetadata& outMetadata)
	{
	}

	static AssetRegistrar reg("jpg",
		[]() { return NewRef<TextureImporter>(); },
		[]() { return NewRef<TextureMetadata>(); });

	static AssetRegistrar reg2("png",
		[]() { return NewRef<TextureImporter>(); },
		[]() { return NewRef<TextureMetadata>(); });
}
