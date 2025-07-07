/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Data/Containers/ReadArray.h>

namespace Flax
{
	/**
	 * @class DataReader
	 * @brief A placeholder class for reading features from data files.
	 */
    struct DataReader
    {
        static ReadArray<c8> ReadData(const String& filePath, b8 emptyOnMissing = false, b8 nullTerminateString = false);
    };
}