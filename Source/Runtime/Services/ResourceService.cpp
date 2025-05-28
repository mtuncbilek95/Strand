#include "ResourceService.h"

namespace Flax
{
	namespace
	{
		struct ResourceServiceRegister
		{
			ResourceServiceRegister()
			{
				ServiceLocator::Register<ResourceService>(NewRef<ResourceService>());
			}
		};

		static ResourceServiceRegister gbResourceService;
	}

	void ResourceService::ResetServiceField()
	{
		m_resources.clear();
	}
}
