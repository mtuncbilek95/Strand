/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/VirtualFile/VFSNode.h>

namespace Flax
{
	class VirtualFileSystem
	{
	public:
		VirtualFileSystem(VFSType type, const String& rootPath);
		~VirtualFileSystem();

		void AddChild(const VFSNodeDesc& desc, VFSNode* pParent = nullptr);
		void RemoveChild(const String& name, VFSNode* pParent = nullptr);
		void RemoveChild(usize index, VFSNode* pParent = nullptr);
		void Clear();

		VFSNode* Parent(const String& name, VFSNode* pParent = nullptr) const;
		VFSNode* Parent(usize index, VFSNode* pParent = nullptr) const;
		VFSNode* Node(const String& name, VFSNode* pParent = nullptr) const;
		VFSNode* Node(usize index, VFSNode* pParent = nullptr) const;
		usize Index(const String& name, VFSNode* pParent = nullptr) const;

	private:
		Owned<VFSNode> m_rootNode;
	};
}
