#include "TextureMetadata.h"

#include <Runtime/Resources/Assets/AssetMetadataRegistry.h>

#include <stb_image.h>

namespace Flax
{
	void TextureMetaExtension::Serialize(Toml& tomlOut)
	{
		toml::array sizeArray;
		sizeArray.push_back(imageSize.x);
		sizeArray.push_back(imageSize.y);
		sizeArray.push_back(imageSize.z);
		tomlOut.emplace("ImageSize", std::move(sizeArray));
		tomlOut.emplace("ImageFormat", u32(imageFormat));
		tomlOut.emplace("MipLevels", mipLevels);
		tomlOut.emplace("ArrayLayers", arrayLayers);
	}

	void TextureMetaExtension::Deserialize(const Toml& tomlIn)
	{
		const auto& sizeArray = *tomlIn.at("ImageSize").as_array();
		imageSize.x = static_cast<u32>(sizeArray[0].as_integer()->get());
		imageSize.y = static_cast<u32>(sizeArray[1].as_integer()->get());
		imageSize.z = static_cast<u32>(sizeArray[2].as_integer()->get());

		imageFormat = static_cast<ImageFormat>(tomlIn.at("ImageFormat").as_integer()->get());
		mipLevels = static_cast<u32>(tomlIn.at("MipLevels").as_integer()->get());
		arrayLayers = static_cast<u32>(tomlIn.at("ArrayLayers").as_integer()->get());
	}

	void TextureMetaExtension::InfoInternal(const Path& assetPath)
	{
		i32 channels = 0, width = 0, height = 0;

		stbi_info(assetPath.string().data(), &width, &height, &channels);

		if (width <= 0 || height <= 0 || channels <= 0)
		{
			Log::Error(LogType::Asset, "Failed to read texture info from '{}'.", assetPath.string());
			return;
		}

		imageSize = Math::Vec3u(static_cast<u32>(width), static_cast<u32>(height), 1);
		mipLevels = 1; // Default to 1 mip level
		arrayLayers = 1; // Default to 1 array layer
		switch (channels)
		{
		case 1: imageFormat = ImageFormat::R8_UNorm; break;
		case 2: imageFormat = ImageFormat::R8G8_UNorm; break;
		case 3: imageFormat = ImageFormat::R8G8B8_UNorm; break;
		case 4: imageFormat = ImageFormat::R8G8B8A8_UNorm; break;
		default: imageFormat = ImageFormat::R8G8B8A8_UNorm; break;
		}
	}

	struct TextureMetaExtensionRegister
	{
		TextureMetaExtensionRegister()
		{
			AssetMetadataRegistry::Get().RegisterMetaExtension<TextureMetaExtension>("texture", "png");
		}
	};
	static TextureMetaExtensionRegister gb_textureMetaExtensionRegister;
}
