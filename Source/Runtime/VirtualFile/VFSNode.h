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
		VFSNode(const VFSNodeDesc& desc, VFSNode* pParent = nullptr);
		~VFSNode();

		void AddChild(const VFSNodeDesc& desc);
		void AddChild(const String& name, VFSNodeType type);
		void AddChild(Ref<VFSNode> node);

		void RemoveChild(const String& name);
		void RemoveChild(VFSNode* node);
		void RemoveChild(const Ref<VFSNode>& node);

		void ClearAll();

		String Name() const { return m_desc.name; }
		VFSNodeType Type() const { return m_desc.type; }
		VFSNode* Parent() const { return m_parent; }
		usize Count() const { return m_children.size(); }

		String RelativePath() const;

		VFSNode* Find(const String& name) const;
		VFSNode* Find(usize index) const;
		Span<Ref<VFSNode>> Children() { return m_children; }

	private:
		VFSNodeDesc m_desc;
		VFSNode* m_parent;

		Vector<Ref<VFSNode>> m_children;
	};
}
