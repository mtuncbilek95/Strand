/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/FileSystem/FileMode.h>

namespace Flax
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
	 * auto vfm = RuntimeService::Get<VirtualFileService>();
	 * 
	 * // "Scripts" and "Assets" are mount points
	 * vfm->Create("Scripts/Player/Enums/PlayerState.h");
	 * vfm->Delete("Assets/Player/Mesh/Textures/AlbedoCharacter.tga");
	 */
	class VirtualFileService : public RuntimeServiceBase
	{
	public:
		VirtualFileService() = default;
		~VirtualFileService() = default;

		void Initialize(const Path& sourcePath);
		void Mount(const Path& mountPoint, Ref<IVirtualFileSystem> fileSystem);
		void Unmount(const Path& mountPoint);

		Ref<IFileStream> Open(const Path& virtPath, FileMode mode);
		b8 Exists(const Path& path) const;
		b8 IsDirectory(const Path& path) const;
		b8 IsFile(const Path& path) const;

		void Create(const Path& path);
		void Delete(const Path& path);
		void Rename(const Path& oldPath, const Path& newPath);
		void Copy(const Path& sourcePath, const Path& destinationPath);
		void Move(const Path& sourcePath, const Path& destinationPath);

		void ResetServiceField() override final;

		Ref<IVirtualFileNode> RootNode(const Path& mountPoint) const;
		Ref<IVirtualFileNode> Node(const Path& virtualPath) const;

	private:
		Path ClearMountPath(const Path& path) const;
		Ref<IVirtualFileSystem> FileSystem(const Path& path) const;

	private:
		HashMap<String, Ref<IVirtualFileSystem>> m_fileSystems;
		Path m_sourcePath;
	};
}
