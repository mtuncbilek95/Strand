/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Instance/GfxType.h>

namespace Flax
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
