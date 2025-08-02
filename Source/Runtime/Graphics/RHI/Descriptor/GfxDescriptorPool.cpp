#include "GfxDescriptorPool.h"

namespace Strand
{
	GfxDescriptorPool::GfxDescriptorPool(const GfxDescriptorPoolDesc& desc, GfxDevice* pDevice) : GfxObject(pDevice),
		m_desc(desc)
	{
	}
}
