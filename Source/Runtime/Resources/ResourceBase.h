/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Resources/ResourceDesc.h>

namespace Strand
{
	STRAND_CLASS()
		class ResourceBase
	{
		STRAND_OBJECT(ResourceBase)
	public:
		ResourceBase(const ResourceDesc& desc);
		~ResourceBase();

		const String& GetResourceName() const { return m_resourceName; }
		const Path& GetRelativePath() const { return m_relativePath; }

	private:
		STRAND_FIELD()
		Uuid m_resourceId;
		STRAND_FIELD()
		String m_resourceName;
		STRAND_FIELD()
		Path m_relativePath;
	};
}