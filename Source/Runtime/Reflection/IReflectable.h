/*
 * Licensed under the terms specified in the LICENSE.md file
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

namespace Strand
{
	struct ClassInfo;

	class IReflectable
	{
	public:
		~IReflectable() = default;

		virtual ClassInfo* GetClass() const = 0;
	};
}