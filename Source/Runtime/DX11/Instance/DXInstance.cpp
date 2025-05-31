#include "DXInstance.h"

#include <Runtime/DX11/Debug/DXDebug.h>

namespace Flax
{
	DXInstance::DXInstance()
	{
		DXDebug::DXAssert(CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(m_instance.GetAddressOf())), "DXInstance()");

        for (u32 i = 0;; ++i)
        {
            if (m_instance->EnumAdapters(i, m_adapter.GetAddressOf()) != S_OK)
                break;

			DXGI_ADAPTER_DESC desc;
			m_adapter->GetDesc(&desc);

			Log::Debug(LogType::GraphicsAPI, "DXInstance: Adapter {}: {}", i, StringHelpers::WStringToString(desc.Description));

			if (desc.DedicatedVideoMemory > 0)
				break;
        }
	}

	DXInstance::~DXInstance()
	{
	}
}
