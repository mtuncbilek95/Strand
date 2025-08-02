#include "GfxSemaphore.h"

namespace Strand
{
	GfxSemaphore::GfxSemaphore(const GfxSemaphoreDesc& desc, GfxDevice* pDevice) : GfxObject(pDevice), 
		m_desc(desc)
	{
	}
}
