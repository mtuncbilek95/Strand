/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/SceneGraph/IComponent.h>

namespace Strand
{
	STRAND_CLASS()
	class NameTagComponent : public IComponent
	{
		STRAND_OBJECT(NameTagComponent)
	public:
		NameTagComponent(const String& entityName) : m_entityName(entityName) 
		{
			m_componentName = NameTagComponent::StaticClassName();
		}
		~NameTagComponent() = default;

		void SetName(const String& newName) { m_entityName = newName; }
		const String& GetName() const { return m_entityName; }

	private:
		STRAND_FIELD()
		String m_entityName;
	};
}