#include "GfxBuffer.h"

namespace Strand
{
	GfxBuffer::GfxBuffer(const GfxBufferDesc& desc, GfxDevice* pDevice) : GfxObject(pDevice), 
		m_desc(desc)
	{
	}
}
