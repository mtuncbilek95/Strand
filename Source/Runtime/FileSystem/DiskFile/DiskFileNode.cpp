#include "DiskFileNode.h"

namespace Flax
{
	DiskFileNode::DiskFileNode(const VirtualNodeDesc& desc, IVirtualFileNode* pParent) : m_desc(desc),
		m_parent(pParent)
	{
	}

	DiskFileNode::~DiskFileNode()
	{
		m_children.clear();
	}

	String DiskFileNode::Name() const
	{
		return m_desc.nodeName;
	}

	Path DiskFileNode::VirtualPath() const
	{
		return m_desc.virtualPath;
	}

	VirtualNodeType DiskFileNode::Type() const
	{
		return m_desc.type;
	}

	IVirtualFileNode* DiskFileNode::Parent()
	{
		return m_parent;
	}

	usize DiskFileNode::Count() const
	{
		if (Type() == VirtualNodeType::File)
			return 0;

		return m_children.size();
	}

	Ref<IVirtualFileNode> DiskFileNode::Child(usize row) const
	{
		if (Type() == VirtualNodeType::File || row < 0 || row >= Count()) {
			return nullptr;
		}
		return m_children[row];
	}

	Ref<IVirtualFileNode> DiskFileNode::Child(const String& objName) const
	{
		for (const auto& child : m_children)
		{
			if (child->Name() == objName)
				return child;
		}

		return nullptr;
	}

	usize DiskFileNode::Index() const
	{
		for(usize i = 0; i < m_parent->Count(); ++i)
		{
			if (m_parent->Child(i).get() == this)
				return i;
		}

		return u64_max; // Not found
	}

	b8 DiskFileNode::IsFolder() const
	{
		return Type() == VirtualNodeType::Folder;
	}

	b8 DiskFileNode::IsFile() const
	{
		return Type() == VirtualNodeType::File;
	}

	void DiskFileNode::Refresh()
	{
		if (m_desc.type != VirtualNodeType::Folder)
			return;

		m_children.clear();
		m_childrenLoaded = false;
	}

	void DiskFileNode::LoadChildren()
	{
		if (m_childrenLoaded || m_desc.type != VirtualNodeType::Folder)
			return;

		for (const auto& entry : FileSys::directory_iterator(m_desc.sourcePath))
		{
		}
	}
}
