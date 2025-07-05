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
	struct ProjectConfigDesc
	{
		Uuid projectId;
		String projectName;
		Math::Vec3u engineVersion;
		DateTime generateDate;
		DateTime lastModifiedDate;
		String description;
		GfxType graphicsApi;
	};
}
