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
	class DXInstance
	{
	public:
		DXInstance();
		~DXInstance();

		IDXGIFactory* Instance() const { return m_instance.Get(); }
		IDXGIAdapter* Adapter() const { return m_adapter.Get(); }

	private:
		ComPtr<IDXGIFactory> m_instance;
		ComPtr<IDXGIAdapter> m_adapter;
	};
}
