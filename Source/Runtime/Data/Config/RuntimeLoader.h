/*
 * Licensed under the terms specified in the LICENSE.md file
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Data/Config/EngineSettings.h>
#include <Runtime/Data/Config/ProjectSettings.h>
namespace Strand
{
	/**
	 * @struct RuntimeLoader
	 * @brief A utility class for loading runtime configs and libraries.
	 */
	struct RuntimeLoader
	{
		static EngineSettings LoadEngineSettings(const Path& path);
		static ProjectSettings LoadProjectSettings(const Path& path);
	};
}
