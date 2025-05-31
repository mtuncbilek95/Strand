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
	class DXInstance;

	class DXDevice
	{
	public:
		DXDevice(DXInstance* pInstance);
		~DXDevice();

		ID3D11Device* Device() const { return m_device.Get(); }
		ID3D11DeviceContext* Context() const { return m_context.Get(); }
		IDXGIFactory* Instance() const { return m_instance; }
		IDXGIAdapter* Adapter() const { return m_adapter; }

	private:
		IDXGIFactory* m_instance;
		IDXGIAdapter* m_adapter;

		ComPtr<ID3D11Device> m_device;
		ComPtr<ID3D11DeviceContext> m_context;
	};
}
