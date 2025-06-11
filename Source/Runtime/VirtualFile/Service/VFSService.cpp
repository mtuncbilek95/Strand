#include "VFSService.h"

namespace Flax
{
	namespace
	{
		struct VFSServiceRegister
		{
			VFSServiceRegister()
			{
				RuntimeService::Register<VFSService>(NewRef<VFSService>());
			}
		};

		static VFSServiceRegister gbVFSService;
	}

	void VFSService::InitVFS(VFSType type, const String& rootPath)
	{
		m_service = NewRef<VirtualFileSystem>(type, rootPath);
	}

	void VFSService::ResetServiceField()
	{
		m_service->Clear();
	}
}
