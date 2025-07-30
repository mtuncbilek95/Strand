/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/FileSystem/IFileStream.h>

namespace Flax
{
	class DiskFileStream : public IFileStream
	{
	public:
		DiskFileStream(const Path& filePath, FileMode mode);
		~DiskFileStream() override;

		usize Read(c8* buffer, usize size) override final;
		usize Write(const c8* buffer, usize size) override final;
		usize Seek(usize offset, i32 origin) override final;
		usize Tell() const override final;

		b8 IsEof() const override final;
		b8 HasError() const override final;
		void Close() override final;

		usize Size() const override final;

	private:
		IosBase::openmode GetOpenMode(FileMode mode) const;
		SeekDir GetSeekDir(i32 origin) const;

	private:
		FileStream m_stream = {};
		Path m_filePath = {};
		FileMode m_mode = {};
		usize m_size = {};
	};
}
