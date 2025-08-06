#include "GfxDescriptorLayout.h"

namespace Strand
{
	GfxDescriptorLayout::GfxDescriptorLayout(const GfxDescriptorLayoutDesc& desc, GfxDevice* pDevice) : GfxObject(pDevice),
		m_desc(desc)
	{
	}
}
