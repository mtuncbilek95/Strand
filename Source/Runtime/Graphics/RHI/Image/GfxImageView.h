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
#include <Runtime/Graphics/RHI/Image/GfxImageViewDesc.h>

namespace Flax
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
