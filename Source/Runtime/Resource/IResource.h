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
	class IResource
	{
	public:
		IResource();
		virtual ~IResource() = default;

		virtual String GetType() = 0;
		virtual void Load() = 0;
		virtual void Unload() = 0;
		virtual b8 IsLoaded() = 0;

		const Uuid& GetId() const { return m_uuid; }

	private:
		Uuid m_uuid;
	};
}
