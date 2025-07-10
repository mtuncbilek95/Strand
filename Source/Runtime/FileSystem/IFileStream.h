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
