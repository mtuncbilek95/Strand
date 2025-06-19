#include "TextureMetadata.h"

#include <Runtime/Resources/Asset/Core/MetadataRegistry.h>

namespace Flax
{
	namespace
	{
		struct TexMetaRegister
		{
			TexMetaRegister() { MetadataRegistry::Get().RegisterMetaType<TextureMetadata>(); }
		};

		static TexMetaRegister texMetaRegistered;
	}
}