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
	class IVirtualFileNode;
	class IFileStream;

	class IVirtualFileSystem
	{
	public:
		virtual ~IVirtualFileSystem() = default;

		virtual void Mount(const Path& mountPoint, const Path& sourcePath) = 0;
		virtual void Unmount(const Path& mountPoint) = 0;

		virtual Ref<IFileStream> Open(const Path& virtualPath, FileMode mode) = 0;
		virtual b8 Exists(const Path& virtualPath) const = 0;
		virtual b8 IsDirectory(const Path& virtualPath) const = 0;
		virtual b8 IsFile(const Path& virtualPath) const = 0;

		virtual void Create(const Path& virtualPath) = 0;
		virtual void Delete(const Path& virtualPath) = 0;
		virtual void Rename(const Path& oldVirtual, const Path& newVirtual) = 0;
		virtual void Copy(const Path& srcVirtual, const Path& dstVirtual) = 0;
		virtual void Move(const Path& srcVirtual, const Path& dstVirtual) = 0;

		virtual Ref<IVirtualFileNode> RootNode() const = 0;
		virtual Ref<IVirtualFileNode> Node(const Path& virtualPath) const = 0;
	};
}
