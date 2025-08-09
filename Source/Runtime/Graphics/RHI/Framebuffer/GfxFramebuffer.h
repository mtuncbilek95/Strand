/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Object/GfxObject.h>
#include <Runtime/Graphics/RHI/Framebuffer/GfxFramebufferDesc.h>

namespace Strand
{
	class GfxFramebuffer : public GfxObject
	{
	public:
		GfxFramebuffer(const GfxFramebufferDesc& desc, GfxDevice* pDevice);
		virtual ~GfxFramebuffer() override = default;

		virtual void* Framebuffer(usize index) const = 0;
		virtual void Resize(const Math::Vec3u& size) = 0;
		
		GfxImageView* ColorView(usize index) const { return m_desc.viewsPerFB[index][0]; }
		GfxImageView* DepthView(usize index) const { return m_desc.viewsPerFB[index][1]; }
		GfxRenderPass* RenderPass() const { return m_desc.passRef; }

	protected:
		usize FrameCount() const { return m_desc.viewsPerFB.size(); }
		usize ImageCount(usize index) const { return m_desc.viewsPerFB[index].size(); }
		GfxImageView* View(usize i, usize j) const { return m_desc.viewsPerFB[i][j]; }

	private:
		GfxFramebufferDesc m_desc;
	};
}