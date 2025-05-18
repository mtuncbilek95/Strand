/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/EntityComponent/Component.h>

namespace Flax
{
	struct TransformComponent : Component<TransformComponent>
	{
		Math::Vec3f position = { 0.f, 0.f, 0.f };
		Math::Quatf rotation = { 0.f, 0.f, 0.f, 1.f };
		Math::Vec3f scale = { 1.f, 1.f, 1.f };
	};
}