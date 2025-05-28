#include "TextureResource.h"

namespace Flax
{
	TextureResource::TextureResource(const TextureResourceProps& desc)
	{
	}

	Ref<IResource> CreateTextureResource(const Any& args)
	{
		const auto& props = std::any_cast<const TextureResourceProps&>(args);
		return NewRef<TextureResource>(props);
	}

	struct TextureResourceRegister
	{
		TextureResourceRegister() { GlobalResourceResolver::RegisterResource("TextureResource", CreateTextureResource); }
	};

	static TextureResourceRegister gbTextureResourceRegistry;
}