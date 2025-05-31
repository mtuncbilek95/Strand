#include "DXSwapchain.h"

#include <Runtime/Window/WindowContext.h>
#include <Runtime/DX11/Device/DXDevice.h>
#include <Runtime/DX11/Debug/DXDebug.h>

namespace Flax
{
	DXSwapchain::DXSwapchain(DXDevice* pDevice)
	{
		BasicWindow* wind = WindowContext::Get().CoreWindow();
		DXGI_SWAP_CHAIN_DESC scDesc = {};
		scDesc.BufferDesc.Width = wind->GetSize().x;
		scDesc.BufferDesc.Height = wind->GetSize().y;
		scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		scDesc.BufferDesc.RefreshRate.Numerator = 60;
		scDesc.BufferDesc.RefreshRate.Denominator = 1;
		scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		scDesc.SampleDesc.Count = 1;
		scDesc.SampleDesc.Quality = 0;
		scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		scDesc.BufferCount = 2;
		scDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		scDesc.Flags = 0;
		scDesc.OutputWindow = HWND(wind->GetHandle());
		scDesc.Windowed = true;

		DXDebug::DXAssert(pDevice->Instance()->CreateSwapChain(pDevice->Device(), &scDesc, &m_swapchain), "DXSwapchain()");
	}

	DXSwapchain::~DXSwapchain()
	{
	}

	ComPtr<ID3D11Texture2D> DXSwapchain::BackBuffer() const
	{
		ComPtr<ID3D11Texture2D> backBuffer;
		m_swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
		return backBuffer;
	}

	void DXSwapchain::Present(UINT syncInterval, UINT flags)
	{
		DXDebug::DXAssert(m_swapchain->Present(syncInterval, flags), "DXSwapchain::Present()");
	}
}
