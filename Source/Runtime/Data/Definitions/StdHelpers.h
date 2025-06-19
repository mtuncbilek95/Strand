/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Data/Definitions/Definitions.h>
#include <Runtime/Data/Definitions/StdNames.h>

namespace Flax
{
	struct StringHelpers
	{
		static String WStringToString(const WString& wstr);
		static WString StringToWString(const String& str);
        static String RemoveExtension(const String& file);
        static String GenerateStringHash(const String& path);
        static String StripExtension(const String& str);
		static String NameWithoutExt(const String& path);
		static String FileExtension(const String& path);
	};
}
