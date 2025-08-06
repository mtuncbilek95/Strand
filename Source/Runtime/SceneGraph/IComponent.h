/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>

namespace Strand
{
	STRAND_CLASS()
	class IComponent
	{
		STRAND_OBJECT(IComponent)
	public:
		virtual ~IComponent() = default;

		b8 IsEnabled() const { return m_enabled; }
		void SetEnabled(b8 state) { m_enabled = state; }

		const String& GetComponentName() const { return m_componentName; }

	protected:
		STRAND_FIELD()
		b8 m_enabled;
		STRAND_FIELD()
		String m_componentName;
	};
}