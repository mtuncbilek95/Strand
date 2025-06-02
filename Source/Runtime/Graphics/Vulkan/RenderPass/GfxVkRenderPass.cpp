#include "GfxVkRenderPass.h"

namespace Flax
{
	GfxVkRenderPass::GfxVkRenderPass(const GfxRenderPassDesc& desc, GfxDevice* pDevice) : GfxRenderPass(desc, pDevice)
	{
	}

	GfxVkRenderPass::~GfxVkRenderPass()
	{
	}

	void* GfxVkRenderPass::Pass() const { return static_cast<void*>(m_pass); }
}
