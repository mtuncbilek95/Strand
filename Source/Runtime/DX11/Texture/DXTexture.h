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
	class DXDevice;

	struct TextureProps
	{
		Math::Vec2u imgSize = { 0, 0 };
		u32 mipLevels = 1;
		u32 arraySize = 1;
		DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM;
		D3D11_RESOURCE_DIMENSION type = D3D11_RESOURCE_DIMENSION_TEXTURE2D;
		u32 sampleCount = 1;
		D3D11_USAGE usage = D3D11_USAGE_DEFAULT;
		D3D11_BIND_FLAG bindFlags = D3D11_BIND_SHADER_RESOURCE;
		u32 stride = 4;
		ReadArray<u8> data;
	};

	class DXTexture
	{
	public:
		DXTexture(const TextureProps& desc, DXDevice* pDevice);
		~DXTexture();

		ID3D11Texture1D* Texture1D() const { return m_texture1D.Get(); }
		ID3D11Texture2D* Texture2D() const { return m_texture2D.Get(); }
		ID3D11Texture3D* Texture3D() const { return m_texture3D.Get(); }

		ID3D11ShaderResourceView* SRV() const { return m_srv.Get(); }

	private:
		TextureProps m_desc;

		ComPtr<ID3D11Texture1D> m_texture1D;
		ComPtr<ID3D11Texture2D> m_texture2D;
		ComPtr<ID3D11Texture3D> m_texture3D;
		ComPtr<ID3D11ShaderResourceView> m_srv;

		DXDevice* m_device;
	};
}
