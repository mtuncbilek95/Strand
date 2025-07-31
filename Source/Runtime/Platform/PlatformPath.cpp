#include "PlatformPath.h"

#if defined(FLAX_WINDOWS)
#include <Runtime/Platform/Win32/Win32Path.h>
typedef Flax::Win32Path DependencyPath;
#else
#warning "Not Implemented Yet"
#endif

namespace Flax
{
	Path PlatformPath::AppDataPath()
	{
		return DependencyPath::AppDataPath();
	}
}
