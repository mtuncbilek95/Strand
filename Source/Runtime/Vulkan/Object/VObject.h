/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <vulkan/vulkan.h>
#include <vma/vk_mem_alloc.h>

namespace Flax
{
	class VDevice;

	class VObject
	{
	public:
		VObject(VDevice* pDevice);
		virtual ~VObject() = default;

		VDevice* GetVkDevice() const { return m_rootDevice; }

	protected:
		VDevice* m_rootDevice;
	};
}
