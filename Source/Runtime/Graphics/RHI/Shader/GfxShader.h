/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Object/GfxObject.h>
#include <Runtime/Graphics/RHI/Shader/GfxShaderDesc.h>

namespace Flax
{
	class GfxShader : public GfxObject
	{
	public:
		GfxShader(const GfxShaderDesc& desc, GfxDevice* pDevice);
		virtual ~GfxShader() override = default;

		virtual void* Shader() const = 0;

		ShaderStage Type() const { return m_desc.stage; }

	private:
		GfxShaderDesc m_desc;
	};
}
