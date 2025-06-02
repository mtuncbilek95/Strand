#include "GfxFence.h"

namespace Flax
{
	GfxFence::GfxFence(const GfxFenceDesc& desc, GfxDevice* pDevice) : GfxObject(pDevice), 
		m_desc(desc)
	{
	}
}
