/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Instance/GfxInstanceDesc.h>
#include <Runtime/Graphics/RHI/Device/GfxDeviceDesc.h>

namespace Flax
{
	class GfxDevice;

	/**
	 * @class GfxInstance
	 * @brief Main instance and gpu device generator for RHI.
	 */
	class GfxInstance
	{
	public:
		GfxInstance(const GfxInstanceDesc& desc); 
		virtual ~GfxInstance() = default;

		virtual Ref<GfxDevice> CreateDevice(const GfxDeviceDesc& desc) = 0;
		virtual void* Instance() const = 0;
		virtual void* Adapter() const = 0;

	private:
		GfxInstanceDesc m_desc;
	};
}
