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
	class IFileStream
	{
	public:
		virtual ~IFileStream() = default;

		virtual usize Read(c8* buffer, usize size) = 0;
		virtual usize Write(const c8* buffer, usize size) = 0;
		virtual usize Seek(usize offset, i32 origin) = 0;
		virtual usize Tell() const = 0;
		
		virtual b8 IsEof() const = 0;
		virtual b8 HasError() const = 0;
		virtual void Close() = 0;

		virtual usize Size() const = 0;
	};
}
