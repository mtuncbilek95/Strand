/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Object/GfxObject.h>
#include <Runtime/Graphics/RHI/Shader/GfxShaderDesc.h>

namespace Strand
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
