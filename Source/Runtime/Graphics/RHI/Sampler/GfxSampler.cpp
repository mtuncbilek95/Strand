#include "GfxSampler.h"

namespace Strand
{
	GfxSampler::GfxSampler(const GfxSamplerDesc& desc, GfxDevice* pDevice) : GfxObject(pDevice), m_desc(desc)
	{
	}
}
