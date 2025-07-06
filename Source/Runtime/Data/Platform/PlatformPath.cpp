#include "PlatformPath.h"

#if defined(FLAX_WINDOWS)
#include <ShlObj.h>
#include <KnownFolders.h>
#include <atlbase.h>
#endif

namespace Flax
{
	String PlatformPath::AppDataPath()
	{
#if defined(FLAX_WINDOWS)
		PWSTR path = nullptr;
		HRESULT hr = SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, nullptr, &path);

		if (SUCCEEDED(hr))
		{
			String str = StringHelpers::WStringToString(path);
			CoTaskMemFree(path);
			return str;
		}
		else
			return String();
#else
#warning "PlatformPath::AppDataPath is not implemented for this platform"
		return String();
#endif
	}
}
