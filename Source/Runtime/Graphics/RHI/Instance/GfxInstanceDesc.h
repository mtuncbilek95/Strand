/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Instance/GfxType.h>

namespace Strand
{
	struct GfxInstanceDesc
	{
		String appName;
		Math::Vec3u appVer;
		GfxType type;

		GfxInstanceDesc& setAppName(const String& name) { appName = name; return *this; }
		GfxInstanceDesc& setAppVersion(const Math::Vec3u& version) { appVer = version; return *this; }
		GfxInstanceDesc& setAPIType(GfxType gfxType) { type = gfxType; return *this; }
	};
}
