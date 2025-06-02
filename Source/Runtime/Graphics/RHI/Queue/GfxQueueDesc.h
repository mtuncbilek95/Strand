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
	enum class QueueType
	{
		Graphics,
		Compute,
		Transfer,
		Sparse
	};

	struct GfxQueueDesc
	{
		QueueType type;
		u32 familyIndex;

		GfxQueueDesc& setType(QueueType t) { type = t; return *this; }
		GfxQueueDesc& setIndex(u32 index) { familyIndex = index; return *this; }
	};
}
