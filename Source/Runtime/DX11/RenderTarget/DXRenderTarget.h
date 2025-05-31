/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>

#include <d3d11.h>
#include <dxgi.h>
#include <wrl/client.h>

using namespace Microsoft::WRL;

namespace Flax
{
	class DXSwapchain;
	class DXDevice;
	
	struct RenderTargetProps
	{
		Math::Vec2u imgSize = { 0, 0 };
		u32 mipLevels = 1;
		u32 arraySize = 1;
		DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM;
		u32 sampleCount = 1;
		D3D11_USAGE usage = D3D11_USAGE_DEFAULT;
		D3D11_BIND_FLAG bindFlags = D3D11_BIND_RENDER_TARGET;
	};

	class DXRenderTarget
	{
	public:
		DXRenderTarget(DXSwapchain* pSwapchain, DXDevice* pDevice);
		DXRenderTarget(const RenderTargetProps& props, DXDevice* pDevice);
		~DXRenderTarget();

		ID3D11RenderTargetView* RTV() const { return m_rtv.Get(); }
		ID3D11RenderTargetView** RTVPtr() { return m_rtv.GetAddressOf(); }
		ID3D11ShaderResourceView* SRV() const { return m_srv.Get(); }
		ID3D11ShaderResourceView** SRVPtr() { return m_srv.GetAddressOf(); }
		ID3D11Texture2D* Texture() const { return m_texture.Get(); }

	private:
		ComPtr<ID3D11Texture2D> m_texture;
		ComPtr<ID3D11RenderTargetView> m_rtv;
		ComPtr<ID3D11ShaderResourceView> m_srv;
	};
}
