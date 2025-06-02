#include "GfxQueue.h"

namespace Flax
{
	GfxQueue::GfxQueue(const GfxQueueDesc& desc, GfxDevice* pDevice) : GfxObject(pDevice), m_desc(desc)
	{
	}
}
