/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Shader/GfxShader.h>

#include <vulkan/vulkan.h>

namespace Strand
{
	class GfxVkShader final : public GfxShader
	{
	public:
		GfxVkShader(const GfxShaderDesc& desc, GfxDevice* pDevice);
		~GfxVkShader() override final;

		void* Shader() const override final;

	private:
		VkShaderModule m_shader;
	};
}
