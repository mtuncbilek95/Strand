#include "StdHelpers.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

namespace Strand
{
    String StringHelpers::WStringToString(const WString& wstr)
    {
        usize requiredSize = 0;
        i32 err = wcstombs_s(&requiredSize, nullptr, 0, wstr.c_str(), _TRUNCATE);
        if (err != 0)
            throw std::runtime_error("Size query failed");

        String str(requiredSize, '\0');
        usize convertedSize = 0;
        err = wcstombs_s(&convertedSize, &str[0], requiredSize, wstr.c_str(), _TRUNCATE);
        if (err != 0)
            throw std::runtime_error("Conversion failed");

        str.resize(convertedSize - 1); // remove null terminator
        return str;
    }

    WString StringHelpers::StringToWString(const String& str)
    {
        usize requiredSize = 0;
        i32 err = mbstowcs_s(&requiredSize, nullptr, 0, str.c_str(), _TRUNCATE);
        if (err != 0)
            throw std::runtime_error("Size query failed");

        WString wstr(requiredSize, L'\0');
        usize convertedSize = 0;
        err = mbstowcs_s(&convertedSize, &wstr[0], requiredSize, str.c_str(), _TRUNCATE);
        if (err != 0)
            throw std::runtime_error("Conversion failed");

        wstr.resize(convertedSize - 1); // remove null terminator
        return wstr;
    }
}