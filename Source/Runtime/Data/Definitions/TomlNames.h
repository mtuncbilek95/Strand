/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#define TOML_EXCEPTIONS 0
#include <toml++/toml.h>

namespace Flax
{
	using Toml = toml::table;

	struct TomlUtils
	{
		static Toml ImportToml(const Path& filePath)
		{
			toml::parse_result result = toml::parse_file(filePath.string());
			if (!result)
			{
				Log::Critical(LogType::IO, "Failed to parse TOML file '{}': '{}'", filePath.string(), result.error().description());
				return Toml();
			}

			return std::move(result.table());
		}
	};
}
