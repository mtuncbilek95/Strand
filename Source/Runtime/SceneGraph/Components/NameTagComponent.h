/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
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
		NameTagComponent(const String& entityName);
		~NameTagComponent() = default;

		void SetName(const String& newName) { m_entityName = newName; }
		const String& GetName() const { return m_entityName; }

	private:
		STRAND_FIELD()
		String m_entityName;
	};
}