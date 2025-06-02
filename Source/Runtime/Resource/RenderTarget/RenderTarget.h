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
	enum class RenderTargetType
	{
		Draw,
		Intermediate,
		ShadowMap,
		Compute,
		Custom
	};

	struct RenderTargetProps final
	{
		RenderTargetType type = RenderTargetType::Draw;
		Math::Vec2u size;
	};

	class RenderTarget : public ResourceBase<RenderTarget>
	{
	public:
		RenderTarget(const RenderTargetProps& desc);
		~RenderTarget();

		Math::Vec2u GetSize() const { return m_props.size; }

	private:
		RenderTargetProps m_props;
	};
}
