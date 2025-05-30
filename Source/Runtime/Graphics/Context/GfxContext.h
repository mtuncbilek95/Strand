/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/Context/GfxContextDesc.h>

namespace Flax
{
	class GfxInstance;
	class GfxDevice;

	class GfxContext : public Singleton<GfxContext>
	{
	public:
		void CreateContext(const GfxContextDesc& desc);

		GfxInstance* Instance() const { return m_instance.get(); }
		GfxDevice* Device() const { return m_device.get(); }

	private:
		Ref<GfxInstance> m_instance;
		Ref<GfxDevice> m_device;
	};
}
