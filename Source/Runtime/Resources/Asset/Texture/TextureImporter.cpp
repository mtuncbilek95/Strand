#include "TextureImporter.h"

#include <Runtime/Resources/Asset/Core/AssetRegistrar.h>
#include <Runtime/Resources/Asset/Texture/TextureMetadata.h>

namespace Flax
{
	ReadArray<u8> ReadJPG(const String& path);
	ReadArray<u8> ReadPNG(const String& path);
	ReadArray<u8> ReadTGA(const String& path);
	ReadArray<u8> ReadHDR(const String& path);
	ReadArray<u8> ReadJPEG(const String& path);

	TextureImporter::~TextureImporter()
	{
	}

	u32 TextureImporter::AssetTypeID() const
	{
		return AssetTypeId::Get().TypeId(AssetTypeName());
	}

	void TextureImporter::Import(const String& sourcePath, AssetMetadata& outMetadata)
	{
	}

	ReadArray<u8> ReadJPG(const String& path)
	{
		return ReadArray<u8>();
	}

	ReadArray<u8> ReadPNG(const String& path)
	{
		return ReadArray<u8>();
	}

	ReadArray<u8> ReadTGA(const String& path)
	{
		return ReadArray<u8>();
	}

	ReadArray<u8> ReadHDR(const String& path)
	{
		return ReadArray<u8>();
	}

	ReadArray<u8> ReadJPEG(const String& path)
	{
		return ReadArray<u8>();
	}

	static AssetRegistrar textureReg("texture", "jpg",
		[]() { return NewRef<TextureImporter>(); },
		[]() { return NewRef<TextureMetadata>(); });

	static AssetRegistrar textureReg2("texture", "jpeg",
		[]() { return NewRef<TextureImporter>(); },
		[]() { return NewRef<TextureMetadata>(); });

	static AssetRegistrar textureReg3("texture", "png",
		[]() { return NewRef<TextureImporter>(); },
		[]() { return NewRef<TextureMetadata>(); });

	static AssetRegistrar textureReg4("texture", "tga",
		[]() { return NewRef<TextureImporter>(); },
		[]() { return NewRef<TextureMetadata>(); });
}
