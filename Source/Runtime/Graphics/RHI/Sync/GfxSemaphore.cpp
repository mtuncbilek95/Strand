#include "GfxSemaphore.h"

namespace Flax
{
	GfxSemaphore::GfxSemaphore(const GfxSemaphoreDesc& desc, GfxDevice* pDevice) : GfxObject(pDevice), 
		m_desc(desc)
	{
	}
}
