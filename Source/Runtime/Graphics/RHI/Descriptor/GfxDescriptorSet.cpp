#include "GfxDescriptorSet.h"

namespace Flax
{
	GfxDescriptorSet::GfxDescriptorSet(const GfxDescriptorSetDesc& desc, GfxDevice* pDevice) : GfxObject(pDevice),
		m_desc(desc)
	{
	}
}
