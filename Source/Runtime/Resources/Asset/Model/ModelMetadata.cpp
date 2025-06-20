#include "ModelMetadata.h"

#include <Runtime/Resources/Asset/Core/MetadataRegistry.h>

namespace Flax
{
	namespace
	{
		struct ModelMetaRegister
		{
			ModelMetaRegister() { MetadataRegistry::Get().RegisterMetaType<ModelMetadata>(); }
		};

		static ModelMetaRegister modelMetaRegistered;
	}
}
