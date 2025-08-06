#include "GfxImageView.h"

namespace Strand
{
	GfxImageView::GfxImageView(const GfxImageViewDesc& desc, GfxDevice* pDevice) : GfxObject(pDevice), 
		m_desc(desc)
	{
	}
}
