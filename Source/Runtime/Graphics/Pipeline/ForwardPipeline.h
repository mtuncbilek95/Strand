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

namespace Flax
{
	class FvkDevice;

	struct ForwardPipelineCreateInfo
	{
		String vPath;
		String fPath;
	};

	class ForwardPipeline
	{
	public:
		ForwardPipeline(const ForwardPipelineCreateInfo& createInfo, FvkDevice* pDevice);
		~ForwardPipeline();

		VkPipeline GetVkPipeline() const { return m_pipeline; }
		VkPipelineLayout GetVkPipelineLayout() const { return m_layout; }
		VkDescriptorSetLayout GetVkLayout() const { return m_descriptorLayout; }

	private:
		VkPipeline m_pipeline;
		VkPipelineLayout m_layout;
		VkDescriptorSetLayout m_descriptorLayout;

		VkShaderModule m_vertexModule;
		VkShaderModule m_fragmentModule;
	};
}
