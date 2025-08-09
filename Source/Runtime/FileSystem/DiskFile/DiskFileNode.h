/*
 * Licensed under the terms specified in the LICENSE.md file
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/FileSystem/IVirtualFileNode.h>

namespace Strand
{
	class DiskFileNode : public IVirtualFileNode
	{
	public:
		DiskFileNode(const VirtualNodeDesc& desc, IVirtualFileNode* pParent = nullptr);
		~DiskFileNode();

		String Name() const override final;
		Path VirtualPath() const override final;
		VirtualNodeType Type() const override final;
		IVirtualFileNode* Parent() override final;
		usize Count() const override final;
		Ref<IVirtualFileNode> Child(usize row) const override final;
		Ref<IVirtualFileNode> Child(const String& objName) const override final;
		IVirtualFileNode* ChildRaw(usize row) const override final;
		IVirtualFileNode* ChildRaw(const String& objName) const override final;
		usize Index() const override final;
		b8 IsFolder() const override final;
		b8 IsFile() const override final;
		void Refresh() override final;

	private:
		void LoadChildren();

	private:
		VirtualNodeDesc m_desc;
		IVirtualFileNode* m_parent;

		Vector<Ref<IVirtualFileNode>> m_children;
		b8 m_childrenLoaded;
	};
}
