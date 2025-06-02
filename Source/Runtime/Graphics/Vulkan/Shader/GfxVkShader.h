/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Shader/GfxShader.h>

#include <vulkan/vulkan.h>

namespace Flax
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
