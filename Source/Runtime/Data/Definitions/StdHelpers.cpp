#include "StdHelpers.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

namespace Flax
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

    String StringHelpers::RemoveExtension(const String& file)
    {
        usize lastDot = file.find_last_of('.');
        if (lastDot != String::npos)
            return file.substr(0, lastDot);
        return file;
    }

    String StringHelpers::GenerateStringHash(const String& path)
    {
        std::ifstream file(path, std::ios::binary);
        if (!file.is_open())
            return "";

        std::ostringstream buffer;
        buffer << file.rdbuf();
        String content = buffer.str();

        u32 hash = 2166136261u;
        for (char c : content)
            hash = (hash ^ static_cast<u8>(c)) * 16777619u;

        std::ostringstream hexStream;
        hexStream << std::hex << std::setw(8) << std::setfill('0') << hash;

        return hexStream.str();
    }

    String StringHelpers::StripExtension(const String& str)
    {
        usize dotPos = str.rfind('.');
        if (dotPos == std::string::npos)
            return str;

        return str.substr(0, dotPos);
    }

	String StringHelpers::NameWithoutExt(const String& path)
	{
		FileSystem::path p(path);
		return p.stem().string();
	}

	String StringHelpers::FileExtension(const String& path)
	{
		FileSystem::path fsPath(path);
		return fsPath.extension().string();
	}
}