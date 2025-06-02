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

	class PipelineState : public ResourceBase<PipelineState>
	{
	public:
		PipelineState(const PipelineStateProps& desc);
		~PipelineState();

	private:
	};
}
