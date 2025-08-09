/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Object/GfxObject.h>
#include <Runtime/Graphics/RHI/Command/GfxCommandPoolDesc.h>

namespace Strand
{
	class GfxCommandBuffer;

	/**
	 * @class GfxCommandPool
	 * @brief All purpose command pool for RHI. CommandPool a.k.a
	 * CommandAllocator is being used for pooling the commandbuffers.
	 */
	class GfxCommandPool : public GfxObject
	{
	public:
		GfxCommandPool(const GfxCommandPoolDesc& desc, GfxDevice* pDevice);
		virtual ~GfxCommandPool() override = default;

		virtual void* Pool() const = 0;
		virtual Ref<GfxCommandBuffer> CreateBuffer(CommandLevel lvl) = 0;

	private:
		GfxCommandPoolDesc m_desc;
	};
}
