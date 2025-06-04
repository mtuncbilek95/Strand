#include "GfxCommandPool.h"

namespace Flax
{
	GfxCommandPool::GfxCommandPool(const GfxCommandPoolDesc& desc, GfxDevice* pDevice) : GfxObject(pDevice),
		m_desc(desc)
	{
	}
}
