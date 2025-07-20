#include "AssetService.h"

#include <Runtime/FileSystem/Service/VirtualFileService.h>
#include <Runtime/Resources/Assets/AssetImportRegistry.h>
#include <Runtime/Resources/Assets/AssetMetadataRegistry.h>

namespace Flax
{
	AssetService::AssetService()
	{
		
	}

	AssetService::~AssetService()
	{
	}

	void AssetService::ImportAsset(const Path& srcPath, const Path& virtualPath)
	{
		auto& metaReg = AssetMetadataRegistry::Get();
		auto* vfm = RuntimeService::Get<VirtualFileService>().get();

		Path dstPath = vfm->VirtualPath(virtualPath);
		dstPath /= srcPath.filename();
		// Extract the extension
		String ext = srcPath.extension().string();
		ext = ext.substr(1);

		String assetType = metaReg.AssetTypeFromExt(ext);
		if (assetType.empty())
		{
			Log::Error(LogType::Asset, "No asset type registered for extension '{}'", ext);
			return;
		}

		AssetMetadataDesc desc = AssetMetadataDesc()
			.setName(srcPath.filename().string())
			.setSrcPath(srcPath) // Should be absolute path
			.setDstPath(dstPath) // Should be something like "Assets/Textures/texture.png"
			.setLastModifiedDate(DateTime::GetCurrentDateTime());

		Ref<AssetMetadata> meta = metaReg.CreateMetadata(assetType, desc);
		if (!meta)
		{
			Log::Error(LogType::Asset, "Failed to create metadata for asset '{}'", srcPath.string());
			return;
		}

		// Serialize metadata to Toml
		Toml tomlOut; 
		meta->Serialize(tomlOut);

		// Save toml to the project domain
		OutFileStream outputFile(vfm->AbsolutePath(dstPath).replace_extension("meta"));
		if (outputFile.is_open())
		{
			outputFile << tomlOut;
			outputFile.close();
			Log::Info(LogType::Asset, "Metadata for asset '{}' saved to '{}'", srcPath.string(), virtualPath.string());
		}
		else
		{
			Log::Error(LogType::Asset, "Failed to save metadata for asset '{}' to '{}'. Check file permissions.", srcPath.string(), virtualPath.string());
			return;
		}

		// Copy the source file to the project domain
		dstPath = vfm->AbsolutePath(dstPath).replace_extension(ext);
		if (!FileSys::copy_file(srcPath, dstPath, FileSys::copy_options::overwrite_existing))
		{
			Log::Error(LogType::Asset, "Failed to copy asset '{}' to '{}'.", srcPath.string(), dstPath.string());
			return;
		}
	}

	void AssetService::InitializeServiceField()
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
