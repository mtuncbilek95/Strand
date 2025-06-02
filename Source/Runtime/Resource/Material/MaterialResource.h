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
	class TextureResource;
	class UniformResource;

	enum class ShaderEntryPoint
	{
		Vertex,
		Fragment
	};

	struct MaterialProps final
	{
		String vPath;
		String fPath;
	};

	class MaterialResource
	{
	public:
		MaterialResource(const MaterialProps& desc);
		~MaterialResource();

		void SetBuffer(u32 set, u32 binding, UniformResource* data);
		void SetTexture(u32 set, u32 binding, TextureResource* data);

	private:
		MaterialProps m_props;

		HashMap<u32, HashMap<u32, TextureResource*>> m_boundTextures;
		HashMap<u32, HashMap<u32, UniformResource*>> m_boundBuffers;
	};
}