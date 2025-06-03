#include "GfxDescriptorPool.h"

namespace Flax
{
	GfxDescriptorPool::GfxDescriptorPool(const GfxDescriptorPoolDesc& desc, GfxDevice* pDevice) : GfxObject(pDevice),
		m_desc(desc)
	{
	}
}
