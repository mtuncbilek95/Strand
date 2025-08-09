/*
 * Licensed under the terms specified in the LICENSE.md file
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Data/Containers/ReadArray.h>

namespace Strand
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