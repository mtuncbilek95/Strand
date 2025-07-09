/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/FileSystem/VirtualNodeDesc.h>

namespace Flax
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
		virtual usize Index() const = 0;
		virtual b8 IsFolder() const = 0;
		virtual b8 IsFile() const = 0;
		virtual void Refresh() = 0;
	};
}
