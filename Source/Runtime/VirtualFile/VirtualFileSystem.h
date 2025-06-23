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

		void AddNode(const String& name, VFSNodeType type, VFSNode* pParent = nullptr);
		void RemoveNode(VFSNode* pChild);

		usize CountOf(const String& name, VFSNode* pParent = nullptr);
		VFSNode* FindNode(const String& name, VFSNode* pParent = nullptr);

	private:
		Ref<VFSNode> m_rootNode;

		VFSType m_type;
		String m_rootPath;
	};
}
