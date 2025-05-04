/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Vulkan/Object/VObject.h>

namespace Flax
{
	class VQueue;
	class VCmdBuffer;

	struct CmdPoolProps final
	{
		VQueue* queue = nullptr;
		VkCommandPoolCreateFlags flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	};

	class VCmdPool final : public VObject
	{
	public:
		VCmdPool(const CmdPoolProps& desc, VDevice* pDevice);
		~VCmdPool() override final;

		inline VkCommandPool GetVkCmdPool() const { return m_cmdPool; }
		VQueue* GetVkQueue() const { return m_props.queue; }

		Ref<VCmdBuffer> CreateCmdBuffer(VkCommandBufferLevel cmdLevel = VK_COMMAND_BUFFER_LEVEL_PRIMARY);

	private:
		CmdPoolProps m_props;

		VkCommandPool m_cmdPool;
	};
}