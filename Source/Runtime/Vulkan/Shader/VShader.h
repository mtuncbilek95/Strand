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
	struct ShaderProps final
	{
		String shaderPath;
		String includePath = "";
		String entryPoint = "main";
		VkShaderStageFlagBits shaderStage;
	};

	class VShader final : public VObject
	{
	public:
		VShader(const ShaderProps& desc, VDevice* pDevice);
		~VShader() override final;

		inline VkShaderModule GetVkShaderModule() const { return m_shaderModule; }
		inline VkShaderStageFlagBits GetVkShaderStage() const { return m_props.shaderStage; }

		const String& GetShaderPath() const { return m_props.shaderPath; }
		const String& GetIncludePath() const { return m_props.includePath; }
		const String& GetEntryPoint() const { return m_props.entryPoint; }

	private:
		ShaderProps m_props;

		VkShaderModule m_shaderModule;
	};
}