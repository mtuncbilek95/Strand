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
	class ImagePixel
	{
	public:
		void ImportPixelData(const String& path);

		Span<c8> Data() const;
		const Math::Vec2u& Size() const;
		u32 Channels() const;

	private:
		ReadArray<c8> m_data;
		Math::Vec2u m_size;
		u32 m_channels;
	};
}
