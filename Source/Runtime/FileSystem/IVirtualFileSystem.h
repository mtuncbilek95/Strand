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
	class IVirtualFileNode;
	class IFileStream;

	class IVirtualFileSystem
	{
	public:
		virtual ~IVirtualFileSystem() = default;

		virtual void Mount(const Path& mountPoint, const Path& sourcePath) = 0;
		virtual void Unmount(const Path& mountPoint) = 0;

		virtual b8 Exists(const Path& virtualPath) const = 0;
		virtual b8 IsDirectory(const Path& virtualPath) const = 0;
		virtual b8 IsFile(const Path& virtualPath) const = 0;
		virtual Path AbsolutePath(const Path& virtualPath) const = 0;
		virtual Path VirtualPath(const Path& absolutePath) const = 0;

		virtual void Create(const Path& virtualPath) = 0;
		virtual void Delete(const Path& virtualPath) = 0;
		virtual void Rename(const Path& oldVirtual, const Path& newVirtual) = 0;
		virtual void Copy(const Path& srcVirtual, const Path& dstVirtual) = 0;
		virtual void Move(const Path& srcVirtual, const Path& dstVirtual) = 0;

		virtual Ref<IVirtualFileNode> Node(const Path& virtualPath) const = 0;
		virtual Ref<IFileStream> Open(const Path& virtualPath, FileMode mode) = 0;
	};
}
