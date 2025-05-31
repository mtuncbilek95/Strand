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

	struct BufferProps
	{
		usize wholeSize;
		usize stride;
		D3D11_USAGE usage;
		u32 bindFlags;
		u32 cpuAccessFlags;
		u32 miscFlags;
		ReadArray<u8> data;
	};

	class DXBuffer
	{
	public:
		DXBuffer(const BufferProps& desc, DXDevice* pDevice);
		~DXBuffer();

		void Update(const ReadArray<u8>& data);
		void Update(void* data, usize size);
		void Map(const ReadArray<u8>& data);
		void Unmap();

		ID3D11Buffer* Buffer() const { return m_buffer.Get(); }
		ID3D11Buffer** BufferPtr() { return m_buffer.GetAddressOf(); }

	private:
		BufferProps m_desc;
		
		ComPtr<ID3D11Buffer> m_buffer;
		DXDevice* m_device = nullptr;
		void* m_mappedData = nullptr;
	};
}
