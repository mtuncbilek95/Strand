#include "DXTexture.h"

#include <Runtime/DX11/Device/DXDevice.h>
#include <Runtime/DX11/Debug/DXDebug.h>

namespace Flax
{
	DXTexture::DXTexture(const TextureProps& desc, DXDevice* pDevice) : m_desc(desc), m_device(pDevice)
	{
		if (desc.type == D3D11_RESOURCE_DIMENSION_TEXTURE1D)
		{

		}
		else if (desc.type == D3D11_RESOURCE_DIMENSION_TEXTURE2D)
		{
			D3D11_TEXTURE2D_DESC depthDesc = {};
			depthDesc.Width = desc.imgSize.x;
			depthDesc.Height = desc.imgSize.y;
			depthDesc.MipLevels = desc.mipLevels;
			depthDesc.ArraySize = desc.arraySize;
			depthDesc.Format = desc.format;
			depthDesc.SampleDesc.Count = desc.sampleCount;
			depthDesc.Usage = desc.usage;
			depthDesc.BindFlags = desc.bindFlags;

			D3D11_SUBRESOURCE_DATA initData = {};
			initData.pSysMem = desc.data.Data();
			initData.SysMemPitch = desc.imgSize.x * desc.stride;
			initData.SysMemSlicePitch = 0;

			DXDebug::DXAssert(pDevice->Device()->CreateTexture2D(&depthDesc, &initData, &m_texture2D), "DXRenderTarget()");
		}
		else
		{

		}
	}

	DXTexture::~DXTexture()
	{
	}
}
