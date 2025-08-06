#include "GfxFramebuffer.h"

namespace Strand
{
	GfxFramebuffer::GfxFramebuffer(const GfxFramebufferDesc& desc, GfxDevice* pDevice) : GfxObject(pDevice), 
		m_desc(desc)
	{
	}
}
