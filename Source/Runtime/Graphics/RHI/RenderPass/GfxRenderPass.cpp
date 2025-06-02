#include "GfxRenderPass.h"

namespace Flax
{
	GfxRenderPass::GfxRenderPass(const GfxRenderPassDesc& desc, GfxDevice* pDevice) : GfxObject(pDevice), 
		m_desc(desc)
	{
	}
}
