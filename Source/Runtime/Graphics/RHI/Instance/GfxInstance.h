/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Instance/GfxInstanceDesc.h>
#include <Runtime/Graphics/RHI/Device/GfxDeviceDesc.h>

namespace Strand
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
