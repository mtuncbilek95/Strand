#include "AssetService.h"

namespace Flax
{
	AssetService::AssetService()
	{
	}

	AssetService::~AssetService()
	{
	}

	void AssetService::LoadSync(const Path& path)
	{
	}

	void AssetService::LoadAsync(const Path& path)
	{
	}

	void AssetService::UnloadSync(const Path& path)
	{
	}

	void AssetService::UnloadAsync(const Path& path)
	{
	}

	void AssetService::UnloadAll()
	{
	}

	void AssetService::ImportToProject(const Path& srcPath, const Path& dstPath)
	{
	}

	void AssetService::ImportToProjectAsync(const Path& srcPath, const Path& dstPath)
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
