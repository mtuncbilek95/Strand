#include "GfxDescriptorSet.h"

namespace Strand
{
	GfxDescriptorSet::GfxDescriptorSet(const GfxDescriptorSetDesc& desc, GfxDevice* pDevice) : GfxObject(pDevice),
		m_desc(desc)
	{
	}
}
