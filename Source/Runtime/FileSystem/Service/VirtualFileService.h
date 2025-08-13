/*
 * Licensed under the terms specified in the LICENSE.md file
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/FileSystem/FileMode.h>

namespace Strand
{
	class IVirtualFileSystem;
	class IVirtualFileNode;
	class IFileStream;

	/**
	 * @class VirtualFileService
	 * 
	 * @brief Main controller for all types of file systems in the
	 * runtime. 
	 * 
	 * @note If doing manipulation on folders/directories, make sure
	 * that the path ends with the directory separator (e.g. "/"). Also
	 * make sure that the path is relative and starts with the mount point.
	 * 
	 * @note If doing manipulation on files, make sure that the path ends
	 * with the file extension (e.g. ".txt"). Also make sure that the path 
	 * is relative and starts with the mount point.
	 * 
	 * Example usage:
	 * 
	 * // Assuming that mount points are set up correctly
	 * auto vfm = ServiceLocator::Get<VirtualFileService>();
	 * 
	 * // "Scripts" and "Assets" are mount points
	 * vfm->Create("Scripts/Player/Enums/PlayerState.h");
	 * vfm->Delete("Assets/Player/Mesh/Textures/AlbedoCharacter.tga");
	 */
	class VirtualFileService : public Service
	{
	public:
		VirtualFileService() = default;
		~VirtualFileService() = default;

		void Initialize(const Path& sourcePath);
		void Mount(const Path& mountPoint, Ref<IVirtualFileSystem> fileSystem);
		void Unmount(const Path& mountPoint);

		b8 Exists(const Path& path) const;
		b8 IsDirectory(const Path& path) const;
		b8 IsFile(const Path& path) const;
		Path AbsolutePath(const Path& path) const;
		Path VirtualPath(const Path& path) const;
		void Refresh(const Path& virtPath) const;

		void Create(const Path& path);
		void Delete(const Path& path);
		void Rename(const Path& oldPath, const Path& newPath);
		void Copy(const Path& sourcePath, const Path& destinationPath);
		void Move(const Path& sourcePath, const Path& destinationPath);

		void InitializeServiceField() override final;
		void ResetServiceField() override final;

		Ref<IVirtualFileSystem> FileSystem(const Path& path) const;
		Ref<IVirtualFileNode> Node(const Path& virtPath);

	private:
		Path ClearMountPath(const Path& path) const;

	private:
		HashMap<String, Ref<IVirtualFileSystem>> m_fileSystems = {};
		Path m_sourcePath = {};
	};
}
