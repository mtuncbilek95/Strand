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
	class VRenderPass;
	class VBuffer;
	class VDescLayout;
	class VDescPool;
	class VDescSet;

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
		VRenderPass* pass;
	};

	class MaterialResource
	{
	public:
		MaterialResource(const MaterialProps& desc);
		~MaterialResource();

		void SetBuffer(u32 set, u32 binding, UniformResource* data);
		void SetTexture(u32 set, u32 binding, TextureResource* data);

		VPipeline* GetPipeline() const { return m_pipeline.get(); }
		VRenderPass* GetUsedRenderPass() const { return m_props.pass; }

	private:
		MaterialProps m_props;

		Ref<VDescLayout> m_layout;
		Ref<VDescPool> m_pool;

		Ref<VPipeline> m_pipeline;
		Ref<VShader> m_vertexShader;
		Ref<VShader> m_fragmentShader;
		  
		Vector<Ref<VDescSet>> m_usedSets;
		HashMap<u32, HashMap<u32, TextureResource*>> m_boundTextures;
		HashMap<u32, HashMap<u32, UniformResource*>> m_boundBuffers;
	};
}