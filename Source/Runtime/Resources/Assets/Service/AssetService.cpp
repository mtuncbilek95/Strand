#include "AssetService.h"

#include <Runtime/Resources/Assets/AssetImportRegistry.h>
#include <Runtime/Resources/Assets/AssetMetadataRegistry.h>

namespace Flax
{
	AssetService::AssetService()
	{
		m_importReg = &AssetImportRegistry::Get();
		m_metaReg = &AssetMetadataRegistry::Get();
	}

	AssetService::~AssetService()
	{
	}

	void AssetService::ImportAsset(const Path& virtualPath)
	{
	}

	void AssetService::ResetServiceField()
	{
	}

	struct AssetServiceRegister
	{
		AssetServiceRegister() { RuntimeService::Register(NewRef<AssetService>()); }
	};
	static AssetServiceRegister gb_assetServiceRegister;
}
