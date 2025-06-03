#include "GfxDescriptorLayout.h"

namespace Flax
{
	GfxDescriptorLayout::GfxDescriptorLayout(const GfxDescriptorLayoutDesc& desc, GfxDevice* pDevice) : GfxObject(pDevice),
		m_desc(desc)
	{
	}
}
