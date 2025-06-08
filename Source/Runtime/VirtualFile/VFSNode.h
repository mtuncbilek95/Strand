/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/VirtualFile/VFSNodeDesc.h>

namespace Flax
{
	class VFSNode
	{
	public:
		VFSNode(const VFSNodeDesc& desc, VFSNode* owner);
		~VFSNode();

		const String& Name() const { return m_desc.name; }
		VFSNodeType Type() const { return m_desc.type; }

		VFSNode* Owner() const { return m_owner; }
		usize Count() const { return m_children.size(); }
		VFSNode* Child(usize index) const;
		VFSNode* Child(const String& name) const;

		void AddChild(const VFSNodeDesc& desc);
		void RemoveChild(const String& name);
		void RemoveChild(usize index);

		void ClearAll();

	private:
		VFSNodeDesc m_desc;

		Vector<Owned<VFSNode>> m_children;
		VFSNode* m_owner;
	};
}
