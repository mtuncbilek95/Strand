/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Util/CommandFormat.h>

namespace Flax
{
	class GfxBuffer;
	class GfxCommandPool;
	class GfxRenderPass;
	class GfxFramebuffer;

	struct CopyBufferDesc
	{
		GfxBuffer* src = nullptr;
		GfxBuffer* dst = nullptr;
		u32 srcOffset = 0;
		u32 dstOffset = 0;
		u32 size = 0;

		CopyBufferDesc& setSrc(GfxBuffer* s) { src = s; return *this; }
		CopyBufferDesc& setDst(GfxBuffer* d) { dst = d; return *this; }
		CopyBufferDesc& setSrcOffset(u32 offset) { srcOffset = offset; return *this; }
		CopyBufferDesc& setDstOffset(u32 offset) { dstOffset = offset; return *this; }
		CopyBufferDesc& setSize(u32 s) { size = s; return *this; }
	};

	struct BeginRenderDesc
	{
		GfxRenderPass* renderPass = nullptr;
		GfxFramebuffer* framebuffer = nullptr;
		u32 frameIndex = 0;
		Math::Vec2u renderArea = {};
		SubpassContent content = SubpassContent::ContentsInline;
		Math::Vec4f colorVal = { .2f, .2f, .2f, 1.f };
		Math::Vec2f depthVal = { 1.f, 0.f };
		b8 clearColor = false;
		b8 clearDepth = false;

		BeginRenderDesc& setRenderPass(GfxRenderPass* pass) { renderPass = pass; return *this; }
		BeginRenderDesc& setFramebuffer(GfxFramebuffer* fb) { framebuffer = fb; return *this; }
		BeginRenderDesc& setFrameIndex(u32 index) { frameIndex = index; return *this; }
		BeginRenderDesc& setRenderArea(Math::Vec2u area) { renderArea = area; return *this; }
		BeginRenderDesc& setContent(SubpassContent c) { content = c; return *this; }
		BeginRenderDesc& setColor(Math::Vec4f color) { colorVal = color; return *this; }
		BeginRenderDesc& setDepth(Math::Vec2f depth) { depthVal = depth; return *this; }
		BeginRenderDesc& setClearColor(b8 color) { clearColor = color; return *this; }
		BeginRenderDesc& setClearDepth(b8 depth) { clearDepth = depth; return *this; }

	};


	struct InheritanceDesc
	{
		GfxRenderPass* renderPass = nullptr;
		GfxFramebuffer* framebuffer = nullptr;
		u32 subpass = 0;
		u32 frameIndex = 0;

		InheritanceDesc& setRenderPass(GfxRenderPass* pass) { renderPass = pass; return *this; }
		InheritanceDesc& setFramebuffer(GfxFramebuffer* fb) { framebuffer = fb; return *this; }
		InheritanceDesc& setFrameIndex(u32 index) { frameIndex = index; return *this; }
	};

	struct GfxCommandBufferDesc
	{
		GfxCommandPool* pool;
		CommandLevel level;

		GfxCommandBufferDesc& setPool(GfxCommandPool* pol) { pool = pol; return *this; }
		GfxCommandBufferDesc& setLevel(CommandLevel lvl) { level = lvl; return *this; }
	};
}
