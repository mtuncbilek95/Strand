/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Vulkan/Buffer/VBuffer.h>
#include <Runtime/Vulkan/Image/VImage.h>
#include <Runtime/Vulkan/Image/VImageView.h>
#include <Runtime/Vulkan/Descriptor/VDescriptorLayout.h>
#include <Runtime/Vulkan/Descriptor/VDescriptorPool.h>
#include <Runtime/Vulkan/Descriptor/VDescriptorSet.h>
#include <Runtime/Vulkan/Pipeline/VPipeline.h>

#include <Runtime/Resource/Geometry/Geometry.h>

namespace Flax
{
	class ShaderResource;
	class PipelineState;

	class Mesh
	{
	public:
		Mesh(const String& meshFolder);
		~Mesh() = default;

		VBuffer* GetBuffer() const { return m_gpuBuffer.get(); }
		PipelineState* GetPSO() const { return m_pipelineResource; }
		
		usize GetVertexCount() const { return m_cpuData.GetVertexCount(); }
		usize GetIndexCount() const { return m_cpuData.GetIndexCount(); }

	private:
		Ref<VBuffer> m_gpuBuffer;
		HashMap<String, Ref<VImage>> m_images;
		HashMap<String, Ref<VImageView>> m_views;

		Ref<VDescLayout> m_descLayout;
		Ref<VDescPool> m_descPool;
		Ref<VDescSet> m_descSet;

		ShaderResource* m_vertResource;
		ShaderResource* m_fragResource;
		PipelineState* m_pipelineResource;

		Ref<VBuffer> m_modelBuffer;

		Geometry m_cpuData;
	};
}
