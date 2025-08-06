#include "GfxShader.h"

namespace Strand
{
	GfxShader::GfxShader(const GfxShaderDesc& desc, GfxDevice* pDevice) : GfxObject(pDevice), 
		m_desc(desc)
	{
	}
}
