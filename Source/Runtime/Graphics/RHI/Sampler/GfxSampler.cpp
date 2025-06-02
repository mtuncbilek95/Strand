#include "GfxSampler.h"

namespace Flax
{
	GfxSampler::GfxSampler(const GfxSamplerDesc& desc, GfxDevice* pDevice) : GfxObject(pDevice), m_desc(desc)
	{
	}
}
