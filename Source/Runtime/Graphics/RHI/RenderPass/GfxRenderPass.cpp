#include "GfxRenderPass.h"

namespace Strand
{
	GfxRenderPass::GfxRenderPass(const GfxRenderPassDesc& desc, GfxDevice* pDevice) : GfxObject(pDevice), 
		m_desc(desc)
	{
	}
}
