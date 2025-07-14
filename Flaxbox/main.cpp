#include <Engine/Resources/Texture/TextureMetadata.h>

#include <iostream>

using namespace Flax;

int main()
{
	AssetMetadata metaTest;
	metaTest.assetName = "TestAsset";
	metaTest.assetType = "texture";
	metaTest.assetPath = "Assets/Textures/TestAsset.png";
	metaTest.assetSize = 12975197825;
	metaTest.lastModifiedDate = DateTime(12, 2, 2025, 16, 30, 22);
	metaTest.metaExtension = NewOwn<TextureMetaExtension>();
	auto* ext = static_cast<TextureMetaExtension*>(metaTest.metaExtension.get());
	ext->imageSize = Math::Vec3u(1024, 1024, 1);
	ext->imageFormat = ImageFormat::R8G8B8A8_UNorm;
	ext->mipLevels = 1;
	ext->arrayLayers = 1;

	Toml tomlToTest;

	metaTest.Serialize(tomlToTest);
	std::cout << std::endl << "----------From Asset----------" << std::endl << tomlToTest << std::endl << "------------------------------" << std::endl;

	AssetMetadata metaFromTest;
	metaFromTest.metaExtension = NewOwn<TextureMetaExtension>();
	metaFromTest.Deserialize(tomlToTest);

	Toml tomlFromTest;
	metaFromTest.Serialize(tomlFromTest);

	std::cout << std::endl << "----------From Toml----------" << std::endl << tomlFromTest << std::endl << "------------------------------" << std::endl;
}