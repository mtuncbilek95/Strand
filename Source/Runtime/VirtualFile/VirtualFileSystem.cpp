#include "VirtualFileSystem.h"

namespace Flax
{
	VirtualFileSystem::VirtualFileSystem(VFSType type, const String& rootPath) : m_type(type), 
		m_rootPath(rootPath)
	{
	}

	VirtualFileSystem::~VirtualFileSystem()
	{
	}
}
