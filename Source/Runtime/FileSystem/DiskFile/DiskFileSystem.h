/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/FileSystem/IVirtualFileSystem.h>

namespace Flax
{
	class DiskFileNode;

	class DiskFileSystem : public IVirtualFileSystem
	{
	public:
		void Mount(const Path& mountPoint, const Path& sourcePath) override final;
		void Unmount(const Path& mountPoint) override final;

		Ref<IFileStream> Open(const Path& virtualPath, FileMode mode) override final;
		b8 Exists(const Path& path) const override final;
		b8 IsDirectory(const Path& path) const override final;
		b8 IsFile(const Path& path) const override final;

		void Create(const Path& virtualPath) override final;
		void Delete(const Path& virtualPath) override final;
		void Rename(const Path& oldVirtual, const Path& newVirtual) override final;
		void Copy(const Path& srcVirtual, const Path& dstVirtual) override final;
		void Move(const Path& srcVirtual, const Path& dstVirtual) override final;

		Ref<IVirtualFileNode> RootNode() const override final;
		Ref<IVirtualFileNode> Node(const Path& virtualPath) const override final;

	private:
		Ref<DiskFileNode> FindNodeInTree(const Path& virtualPath) const;
		Path ToRealPath(const Path& virtualPath) const;
		Path ToVirtualPath(const Path& realPath) const;

	private:
		Path m_sourcePath;
		Path m_mountPoint;

		Ref<DiskFileNode> m_rootNode;
	};
}
