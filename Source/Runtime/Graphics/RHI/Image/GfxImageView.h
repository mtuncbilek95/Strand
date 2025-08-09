/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Object/GfxObject.h>
#include <Runtime/Graphics/RHI/Image/GfxImageViewDesc.h>

namespace Strand
{
	/**
	 * @class GfxImageView
	 * @brief GPU representation of the image buffers.
	 */
	class GfxImageView : public GfxObject
	{
	public:
		GfxImageView(const GfxImageViewDesc& desc, GfxDevice* pDevice);
		virtual ~GfxImageView() override = default;

		virtual void* Image() const = 0;
		virtual void* View() const = 0;

	private:
		GfxImageViewDesc m_desc;
	};
}
