#include "PlatformPath.h"

#if defined(STRAND_WINDOWS)
#include <Runtime/Platform/Win32/Win32Path.h>
typedef Strand::Win32Path DependencyPath;
#else
#warning "Not Implemented Yet"
#endif

namespace Strand
{
	Path PlatformPath::AppDataPath()
	{
		return DependencyPath::AppDataPath();
	}
}
