/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/FileSystem/VirtualNodeType.h>

namespace Flax
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
