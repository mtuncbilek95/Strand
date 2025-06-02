#include "GfxImageView.h"

namespace Flax
{
	GfxImageView::GfxImageView(const GfxImageViewDesc& desc, GfxDevice* pDevice) : GfxObject(pDevice), 
		m_desc(desc)
	{
	}
}
