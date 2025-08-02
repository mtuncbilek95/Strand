#include "GfxFence.h"

namespace Strand
{
	GfxFence::GfxFence(const GfxFenceDesc& desc, GfxDevice* pDevice) : GfxObject(pDevice), 
		m_desc(desc)
	{
	}
}
