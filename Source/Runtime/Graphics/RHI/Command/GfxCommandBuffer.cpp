#include "GfxCommandBuffer.h"

namespace Strand
{
	GfxCommandBuffer::GfxCommandBuffer(const GfxCommandBufferDesc& desc, GfxDevice* pDevice) : GfxObject(pDevice),
		m_desc(desc)
	{

	}
}
