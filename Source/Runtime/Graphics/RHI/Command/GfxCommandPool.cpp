#include "GfxCommandPool.h"

namespace Strand
{
	GfxCommandPool::GfxCommandPool(const GfxCommandPoolDesc& desc, GfxDevice* pDevice) : GfxObject(pDevice),
		m_desc(desc)
	{
	}
}
