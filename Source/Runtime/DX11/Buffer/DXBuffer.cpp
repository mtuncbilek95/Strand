#include "DXBuffer.h"

#include <Runtime/DX11/Device/DXDevice.h>
#include <Runtime/DX11/Debug/DXDebug.h>

namespace Flax
{
	DXBuffer::DXBuffer(const BufferProps& desc, DXDevice* pDevice) : m_desc(desc), m_device(pDevice)
	{
		D3D11_BUFFER_DESC bufDesc = {};
		bufDesc.Usage = desc.usage;

		if (desc.bindFlags & D3D11_BIND_CONSTANT_BUFFER)
		{
			usize originalSize = desc.wholeSize;
			usize alignedSize = (originalSize + 255) & ~255;
			bufDesc.ByteWidth = alignedSize;
		}
		else
			bufDesc.ByteWidth = desc.data.SizeInBytes();

		bufDesc.BindFlags = desc.bindFlags;
		bufDesc.CPUAccessFlags = desc.cpuAccessFlags;
		bufDesc.MiscFlags = desc.miscFlags;
		bufDesc.StructureByteStride = desc.stride;

		// If the cpu accesse is write, its probably constant buffer
		if (desc.cpuAccessFlags & D3D11_CPU_ACCESS_WRITE)
		{
			DXDebug::DXAssert(pDevice->Device()->CreateBuffer(&bufDesc, nullptr, &m_buffer), "DXBuffer()");

			/*D3D11_MAPPED_SUBRESOURCE mapped;
			DXDebug::DXAssert(pDevice->Context()->Map(m_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped), "DXBuffer()");
			m_mappedData = mapped.pData;*/

			/*if (desc.data.SizeInBytes() > 0)
				memcpy(mapped.pData, desc.data.Data(), desc.data.SizeInBytes());*/
		}
		else
		{
			D3D11_SUBRESOURCE_DATA initData = {};
			initData.pSysMem = desc.data.Data();

			DXDebug::DXAssert(pDevice->Device()->CreateBuffer(&bufDesc, &initData, &m_buffer), "DXBuffer()");
		}
	}

	DXBuffer::~DXBuffer()
	{
	}

	void DXBuffer::Update(const ReadArray<u8>& data)
	{
		// If the cpu access is write, we already mappped the buffer. So just memcpy.
		if (m_desc.cpuAccessFlags & D3D11_CPU_ACCESS_WRITE)
			memcpy(m_mappedData, data.Data(), data.SizeInBytes());
		else
		{
			D3D11_MAPPED_SUBRESOURCE mapped;
			DXDebug::DXAssert(m_device->Context()->Map(m_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped), "DXBuffer::Update()");
			memcpy(mapped.pData, data.Data(), data.SizeInBytes());
			m_device->Context()->Unmap(m_buffer.Get(), 0);
		}
	}

	void DXBuffer::Update(void* data, usize size)
	{
		D3D11_MAPPED_SUBRESOURCE mapped;
		DXDebug::DXAssert(m_device->Context()->Map(m_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped), "DXBuffer::Update()");
		memcpy(mapped.pData, data, size);
		m_device->Context()->Unmap(m_buffer.Get(), 0);
	}

	void DXBuffer::Map(const ReadArray<u8>& data)
	{
		if (m_desc.cpuAccessFlags & D3D11_CPU_ACCESS_WRITE)
			return;
		else
		{
			D3D11_MAPPED_SUBRESOURCE mapped;
			DXDebug::DXAssert(m_device->Context()->Map(m_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped), "DXBuffer::Map()");
			memcpy(mapped.pData, data.Data(), data.SizeInBytes());
			m_mappedData = mapped.pData;
		}
	}

	void DXBuffer::Unmap()
	{
		if (m_desc.cpuAccessFlags & D3D11_CPU_ACCESS_WRITE)
			return;
		else
		{
			m_device->Context()->Unmap(m_buffer.Get(), 0);
			m_mappedData = nullptr;
		}
	}
}