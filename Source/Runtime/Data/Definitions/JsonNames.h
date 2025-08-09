/*
 * Licensed under the terms specified in the LICENSE.md file
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <nlohmann/json.hpp>

namespace Strand
{
	using Json = nlohmann::json;
	using OrderedJson = nlohmann::ordered_json;
}
