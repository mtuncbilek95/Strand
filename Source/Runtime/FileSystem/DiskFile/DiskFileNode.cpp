#include "DiskFileNode.h"

namespace Flax
{
	DiskFileNode::DiskFileNode(const VirtualNodeDesc& desc, IVirtualFileNode* pParent) : m_desc(desc),
		m_parent(pParent), m_childrenLoaded(desc.type == VirtualNodeType::File)
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

	IVirtualFileNode* DiskFileNode::ChildRaw(usize row) const
	{
		if (Type() == VirtualNodeType::File || row < 0 || row >= Count()) {
			return nullptr;
		}
		return m_children[row].get();
	}

	IVirtualFileNode* DiskFileNode::ChildRaw(const String& objName) const
	{
		for (const auto& child : m_children)
		{
			if (child->Name() == objName)
				return child.get();
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

		LoadChildren();
	}

	void DiskFileNode::LoadChildren()
	{
		if (m_childrenLoaded || m_desc.type != VirtualNodeType::Folder)
			return;

		for (const auto& entry : FileSys::directory_iterator(m_desc.sourcePath))
		{
			if (entry.path().filename() == "." || entry.path().filename() == "..")
				continue; // Skip current and parent directory entries

			Path childVirtualPath = m_desc.virtualPath / entry.path().filename();
			Path childRealPath = entry.path();

			VirtualNodeType childType = VirtualNodeType::None;
			if (entry.is_directory())
				childType = VirtualNodeType::Folder;
			else if (entry.is_regular_file())
				childType = VirtualNodeType::File;

			VirtualNodeDesc childDesc = VirtualNodeDesc().setName(entry.path().filename().string())
				.setVirtualPath(childVirtualPath)
				.setSourcePath(childRealPath)
				.setType(childType);

			Ref<DiskFileNode> childNode = NewRef<DiskFileNode>(childDesc, this);
			m_children.push_back(childNode);
		}

		std::sort(m_children.begin(), m_children.end(), [](const Ref<IVirtualFileNode>& a, const Ref<IVirtualFileNode>& b) {
			if (a->IsFolder() && !b->IsFolder()) return true;
			if (!a->IsFolder() && b->IsFolder()) return false;
			return a->Name() < b->Name();
			});

		m_childrenLoaded = true;
	}
}
