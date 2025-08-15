/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Resources/ResourceDesc.h>

namespace Strand
{
	STRAND_CLASS();
	class ResourceBase : public IReflectable
	{
		STRAND_OBJECT(ResourceBase);
	public:
		ResourceBase(const ResourceDesc& desc);
		virtual ~ResourceBase();

		const String& GetResourceName() const { return m_resourceName; }
		const Path& GetRelativePath() const { return m_relativePath; }

	private:
		STRAND_FIELD();
		Uuid m_resourceId;
		STRAND_FIELD();
		String m_resourceName;
		STRAND_FIELD();
		Path m_relativePath;
	};
}