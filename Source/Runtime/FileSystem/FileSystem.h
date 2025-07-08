/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>

namespace Flax
{
	class FileSystem : public RuntimeServiceBase
	{
	public:
		FileSystem() = default;
		~FileSystem() = default;

		void SetRootPath(const Path& path);
		const Path& RootPath() const;

		void NewDirectory(const Path& path);
		void DeleteDirectory(const Path& path);

		void NewFile(const Path& path);
		void RemoveFile(const Path& path);
		void RenameFile(const Path& oldPath, const Path& newPath);
		void DuplicateFile(const Path& sourcePath, const Path& destinationPath);
		void RouteFile(const Path& sourcePath, const Path& destinationPath);

		b8 Exists(const Path& path) const;
		b8 IsDirectory(const Path& path) const;
		b8 IsFile(const Path& path) const;

		Path SeparatePathFromRoot(const Path& path) const;
		Path ExtractPath(const Path& path) const;
		String ExtractFileName(const Path& path) const;
		String ExtractExtension(const Path& path) const;
		String ExtractFileWExt(const Path& path) const;

		void ResetServiceField() override final;

	private:
		Path m_rootPath;
	};
}
