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
}
