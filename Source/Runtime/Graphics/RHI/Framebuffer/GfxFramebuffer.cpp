#include "GfxFramebuffer.h"

namespace Flax
{
	GfxFramebuffer::GfxFramebuffer(const GfxFramebufferDesc& desc, GfxDevice* pDevice) : GfxObject(pDevice), 
		m_desc(desc)
	{
	}
}
