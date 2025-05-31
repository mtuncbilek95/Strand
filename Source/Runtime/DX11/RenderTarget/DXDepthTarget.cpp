#include "DXDepthTarget.h"

#include <Runtime/DX11/Device/DXDevice.h>
#include <Runtime/DX11/Debug/DXDebug.h>

namespace Flax
{
	DXDepthTarget::DXDepthTarget(const DepthTargetProps& desc, DXDevice* pDevice)
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

		DXDebug::DXAssert(pDevice->Device()->CreateTexture2D(&depthDesc, nullptr, &m_texture), "DXDepthTarget()");
		DXDebug::DXAssert(pDevice->Device()->CreateDepthStencilView(m_texture.Get(), nullptr, &m_dsv), "DXDepthTarget()");

		if (desc.bindFlags & D3D11_BIND_SHADER_RESOURCE)
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
			srvDesc.Format = desc.format;
			srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			srvDesc.Texture2D.MostDetailedMip = 0;
			srvDesc.Texture2D.MipLevels = desc.mipLevels;
			DXDebug::DXAssert(pDevice->Device()->CreateShaderResourceView(m_texture.Get(), &srvDesc, &m_srv), "DXDepthTarget()");
		}
	}

	DXDepthTarget::~DXDepthTarget()
	{
	}
}
