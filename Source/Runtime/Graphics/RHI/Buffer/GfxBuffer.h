/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Object/GfxObject.h>
#include <Runtime/Graphics/RHI/Buffer/GfxBufferDesc.h>

namespace Flax
{
	/**
	 * @class GfxBuffer
	 * @brief General purpose buffer for RHI. It can be used for Vertex, 
	 * Index, Uniform(Constant), Storage and Staging. The Descriptor Buffer
	 * will be found in Source/Runtime/Graphics/RHI/Descriptor/GfxDescriptorBuffer.h
	 */
	class GfxBuffer : public GfxObject
	{
	public:
		GfxBuffer(const GfxBufferDesc& desc, GfxDevice* pDevice);
		virtual ~GfxBuffer() override = default;

		virtual void* Buffer() const = 0;
		virtual void Update(const ReadArray<u8>& data) = 0;
		virtual void Update(void* buffer, usize size) = 0;
		virtual void Map(const ReadArray<u8>& data) = 0;
		virtual void Map(void* buffer, usize size) = 0;
		virtual void Unmap() = 0;

		usize SizeInBytes() const { return m_desc.sizeInBytes; }

	private:
		GfxBufferDesc m_desc;
	};
}
