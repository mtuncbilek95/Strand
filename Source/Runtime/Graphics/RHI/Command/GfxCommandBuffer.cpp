#include "GfxCommandBuffer.h"

namespace Flax
{
	GfxCommandBuffer::GfxCommandBuffer(const GfxCommandBufferDesc& desc, GfxDevice* pDevice) : GfxObject(pDevice),
		m_desc(desc)
	{

	}
}
