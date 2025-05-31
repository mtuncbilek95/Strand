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

	enum class ShaderType
	{
		Vertex,
		Geometry,
		Fragment,
		Compute
	};

	struct ShaderProps
	{
		String path;
		ShaderType type;
		String entry;
		String model;
	};

	class DXShader
	{
	public:
		DXShader(const ShaderProps& desc, DXDevice* pDevice);
		~DXShader();

		ID3D11VertexShader* Vertex() const { return m_vertex.Get(); }
		ID3D11PixelShader* Pixel() const { return m_pixel.Get(); }

	private:
		ShaderProps m_desc;

		ComPtr<ID3D11VertexShader> m_vertex;
		ComPtr<ID3D11PixelShader> m_pixel;

		DXDevice* m_device;

		ComPtr<ID3DBlob> m_data;
	};
}
