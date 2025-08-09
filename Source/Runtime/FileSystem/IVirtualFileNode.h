/*
 * Licensed under the terms specified in the LICENSE.md file
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/FileSystem/VirtualNodeDesc.h>

namespace Strand
{
	class IVirtualFileNode
	{
	public:
		virtual ~IVirtualFileNode() = default;

		virtual String Name() const = 0;
		virtual Path VirtualPath() const = 0;
		virtual VirtualNodeType Type() const = 0;
		virtual IVirtualFileNode* Parent() = 0;
		virtual usize Count() const = 0;
		virtual Ref<IVirtualFileNode> Child(usize row) const = 0;
		virtual Ref<IVirtualFileNode> Child(const String& objName) const = 0;
		virtual IVirtualFileNode* ChildRaw(usize row) const = 0;
		virtual IVirtualFileNode* ChildRaw(const String& objName) const = 0;
		virtual usize Index() const = 0;
		virtual b8 IsFolder() const = 0;
		virtual b8 IsFile() const = 0;
		virtual void Refresh() = 0;
	};
}
