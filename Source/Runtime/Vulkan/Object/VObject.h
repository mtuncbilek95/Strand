/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Data/Containers/IObject.h>

#include <vulkan/vulkan.h>
#include <vma/vk_mem_alloc.h>
#include <Volk/volk.h>

namespace Flax
{
	class VDevice;
	class VCmdBuffer;
	class VSemaphore;
	class VFence;

	class VObject : public IObject
	{
	public:
		VObject(VDevice* pDevice) : m_rootDevice(pDevice) {}
		virtual ~VObject() override = default;

		inline VDevice* GetRoot() const { return m_rootDevice; }

	private:
		VDevice* m_rootDevice;
	};
}