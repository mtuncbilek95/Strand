#include "DXShader.h"

#include <Runtime/DX11/Device/DXDevice.h>
#include <Runtime/DX11/Debug/DXDebug.h>

#include <d3dcompiler.h>

namespace Flax
{
	DXShader::DXShader(const ShaderProps& desc, DXDevice* pDevice) : m_desc(desc), m_device(pDevice)
	{
		ComPtr<ID3DBlob> errorBlob;
        WString path = StringHelpers::StringToWString(desc.path);
		DXDebug::DXAssert(D3DCompileFromFile(path.data(), nullptr, nullptr, desc.entry.data(), desc.model.data(), 0, 0, &m_data, &errorBlob), "DXShader()");

		switch (desc.type)
		{
		case ShaderType::Vertex:
			DXDebug::DXAssert(pDevice->Device()->CreateVertexShader(m_data->GetBufferPointer(), m_data->GetBufferSize(), nullptr, &m_vertex), "DXShader()");
			break;
		case ShaderType::Fragment:
			DXDebug::DXAssert(pDevice->Device()->CreatePixelShader(m_data->GetBufferPointer(), m_data->GetBufferSize(), nullptr, &m_pixel), "DXShader()");
			break;
		default:
			Log::Critical(LogType::GraphicsAPI, "Unknown type of shader");
			break;
		}
	}

	DXShader::~DXShader()
	{
	}
}
