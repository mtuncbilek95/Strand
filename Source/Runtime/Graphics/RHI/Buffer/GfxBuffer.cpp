#include "GfxBuffer.h"

namespace Flax
{
	GfxBuffer::GfxBuffer(const GfxBufferDesc& desc, GfxDevice* pDevice) : GfxObject(pDevice), 
		m_desc(desc)
	{
	}
}
