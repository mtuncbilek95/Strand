#include "GfxQueue.h"

namespace Strand
{
	GfxQueue::GfxQueue(const GfxQueueDesc& desc, GfxDevice* pDevice) : GfxObject(pDevice), m_desc(desc)
	{
	}
}
