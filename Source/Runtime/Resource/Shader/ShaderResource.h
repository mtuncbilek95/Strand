/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Resource/IResource.h>
#include <Runtime/Vulkan/Shader/VShader.h>

namespace Flax
{
	struct ShaderResourceProps final
	{
		VkShaderStageFlagBits stageType;
		String path;
	};

	class ShaderResource : public IResource
	{
	public:
		ShaderResource(const ShaderResourceProps& desc);
		~ShaderResource();

		void Compile();

		VShader* GetShader() const { return m_shader.get(); }
		String GetType() override { return "ShaderResource"; }

	private:
		ShaderResourceProps m_props;

		Ref<VShader> m_shader;
	};
}