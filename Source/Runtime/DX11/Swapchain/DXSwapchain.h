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

	class DXSwapchain
	{
	public:
		DXSwapchain(DXDevice* pDevice);
		~DXSwapchain();
		
		IDXGISwapChain* Swapchain() const { return m_swapchain.Get(); }
		ComPtr<ID3D11Texture2D> BackBuffer() const;

		void Present(UINT syncInterval, UINT flags);

	private:
		ComPtr<IDXGISwapChain> m_swapchain;
	};
}
