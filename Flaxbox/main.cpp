#include <Runtime/Graphics/Vulkan/Instance/GfxVkInstance.h>

using namespace Flax;

int main()
{
	GfxInstanceDesc instDesc = GfxInstanceDesc().setAppVersion({ 1, 0, 0 })
		.setAppName("Flaxbox")
		.setAPIType(GfxType::Vulkan);

	Ref<GfxInstance> instance = NewRef<GfxVkInstance>(instDesc);
}