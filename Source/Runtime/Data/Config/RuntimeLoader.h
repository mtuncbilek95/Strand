/*
/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Data/Config/EngineSettings.h>
#include <Runtime/Data/Config/ProjectSettings.h>
namespace Flax
{
	/**
	 * @struct RuntimeLoader
	 * @brief A utility class for loading runtime configs and libraries.
	 */
	struct RuntimeLoader
	{
		RuntimeLoader() = delete; // Makes a static class

		static EngineSettings LoadEngineSettings(const Path& path);
		static ProjectSettings LoadProjectSettings(const Path& path);
	};
}
