/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>

namespace Strand
{
	STRAND_CLASS()
	class IComponent : public IReflectable
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