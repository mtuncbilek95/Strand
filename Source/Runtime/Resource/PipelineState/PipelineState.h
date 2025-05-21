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

namespace Flax
{
	class ShaderResource;
	class RenderTarget;
	class VDescLayout;
	class VPipeline;

	enum class PipelineStage
	{
		Vertex,
		Geometry,
		TesselationEval,
		TesselationControl,
		Compute,
		Fragment,
		Count
	};

	struct PipelineStateProps final
	{
		HashMap<PipelineStage, ShaderResource*> shaders;
		RenderTarget* renderTarget;
	};

	class PipelineState : public IResource
	{
	public:
		PipelineState(const PipelineStateProps& desc);
		~PipelineState() override;

		String GetType() override { return "PipelineStateObject"; }
		void Load() override {}
		void Unload() override {}
		b8 IsLoaded() override { return false; }

		VPipeline* GetPipeline() const { return m_pipeline.get(); }
		VDescLayout* GetLayout() const { return m_layout.get(); }
		RenderTarget* GetTarget() const { return m_props.renderTarget; }

	private:
		PipelineStateProps m_props;

		Ref<VDescLayout> m_layout;
		Ref<VPipeline> m_pipeline;
	};
}
