#include "GfxShader.h"

namespace Flax
{
	GfxShader::GfxShader(const GfxShaderDesc& desc, GfxDevice* pDevice) : GfxObject(pDevice), 
		m_desc(desc)
	{
	}
}
