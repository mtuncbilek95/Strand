#include "DXDevice.h"

#include <Runtime/DX11/Instance/DXInstance.h>
#include <Runtime/DX11/Debug/DXDebug.h>

namespace Flax
{
	DXDevice::DXDevice(DXInstance* pInstance) : m_instance(pInstance->Instance()), m_adapter(pInstance->Adapter())
	{
		// Create the device
		D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;
		HRESULT hr = D3D11CreateDevice(m_adapter, D3D_DRIVER_TYPE_UNKNOWN, nullptr, D3D11_CREATE_DEVICE_DEBUG,
			&featureLevel, 1, D3D11_SDK_VERSION, &m_device, nullptr, &m_context);
		DXDebug::DXAssert(hr, "DXDevice()");
	}

	DXDevice::~DXDevice()
	{
	}
}
