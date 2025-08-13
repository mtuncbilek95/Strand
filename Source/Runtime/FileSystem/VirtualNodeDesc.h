/*
 * Licensed under the terms specified in the LICENSE.md file
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/FileSystem/VirtualNodeType.h>

namespace Strand
{
	struct VirtualNodeDesc
	{
		String nodeName = {};
		Path virtualPath = {};
		Path sourcePath = {};
		VirtualNodeType type = {};

		VirtualNodeDesc& setName(const String& name) noexcept { nodeName = name; return *this; }
		VirtualNodeDesc& setVirtualPath(const Path& path) noexcept { virtualPath = path; return *this; }
		VirtualNodeDesc& setSourcePath(const Path& path) noexcept { sourcePath = path; return *this; }
		VirtualNodeDesc& setType(VirtualNodeType nodeType) noexcept { type = nodeType; return *this; }
	};
}
