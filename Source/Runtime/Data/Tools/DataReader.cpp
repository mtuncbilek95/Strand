#include "DataReader.h"

#include <fstream>
#include <sstream>
#include <iostream>

namespace Flax
{
    ReadArray<c8> DataReader::ReadData(const String& filePath, b8 emptyOnMissing, b8 nullTerminateString)
    {
        std::ifstream file(filePath, std::ios::ate | std::ios::binary);

        if (!file.is_open())
        {
            if (emptyOnMissing)
                return {};

            throw std::runtime_error("Failed to open file '" + filePath + "'!");
        }

        const usize fileSize = static_cast<usize>(file.tellg());
        ReadArray<c8> data(fileSize + nullTerminateString);

        file.seekg(0);
        file.read(data.Data(), fileSize);

        if (nullTerminateString)
            data[fileSize] = '\0';

        file.close();
        return data;
    }
}