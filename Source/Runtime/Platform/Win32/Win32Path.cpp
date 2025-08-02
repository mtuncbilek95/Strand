#include "Win32Path.h"

#if defined(FLAX_WINDOWS)
#include <ShlObj.h>
#include <KnownFolders.h>
#include <atlbase.h>
#endif

namespace Strand
{
	Path Win32Path::AppDataPath()
	{
#if defined(FLAX_WINDOWS)
		PWSTR path = nullptr;
		HRESULT hr = SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, nullptr, &path);

		if (SUCCEEDED(hr))
		{
			Path str = StringHelpers::WStringToString(path);
			CoTaskMemFree(path);
			return str;
		}
		else
			return Path();
#else
#warning "Win32Path::AppDataPath doesnt belong to the current platform"
		return Path();
#endif
	}
}
