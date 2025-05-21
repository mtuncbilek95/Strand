/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>

namespace Flax
{
	class VPipeline;
	class VShader;
	class VRenderpass;

	struct MaterialProps final
	{
		String vPath;
		String fPath;
		VRenderpass* pass;
	};

	class MaterialResource
	{
	public:
		MaterialResource() = default;
		~MaterialResource() = default;

	private:
		Ref<VPipeline> m_pipeline;
		Ref<VShader> m_vertexShader;
		Ref<VShader> m_fragmentShader;
	};
}