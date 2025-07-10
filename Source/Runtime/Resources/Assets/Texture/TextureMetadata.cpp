#include "TextureMetadata.h"

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
}
