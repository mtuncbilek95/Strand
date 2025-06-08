#include "VFSNode.h"

namespace Flax
{
	VFSNode::VFSNode(const VFSNodeDesc& desc, VFSNode* owner) : m_desc(desc), 
		m_owner(owner)
	{
	}

	VFSNode::~VFSNode()
	{
		ClearAll();
	}

	VFSNode* VFSNode::Child(usize index) const
	{
		if (index > m_children.size())
		{
			Log::Critical(LogType::VFS, "Index is bigger than the actual length of this node '{}'.", m_desc.name);
			return nullptr;
		}

		return m_children[index].get();
	}

	VFSNode* VFSNode::Child(const String& name) const
	{
		for (const auto& child : m_children)
		{
			if (child->m_desc.name == name)
				return child.get();
		}

		Log::Critical(LogType::VFS, "Child with name '{}' not found in node '{}'.", name, m_desc.name);
		return nullptr;
	}

	void VFSNode::AddChild(const VFSNodeDesc& desc)
	{
		if (Child(desc.name))
		{
			Log::Critical(LogType::VFS, "Child with name '{}' already exists in node '{}'.", desc.name, m_desc.name);
			return;
		}

		m_children.push_back(std::make_unique<VFSNode>(desc, this));
	}

	void VFSNode::RemoveChild(const String& name)
	{
		for (auto it = m_children.begin(); it != m_children.end(); ++it)
		{
			if ((*it)->m_desc.name == name)
			{
				m_children.erase(it);
				return;
			}
		}
		Log::Critical(LogType::VFS, "Child with name '{}' not found in node '{}'.", name, m_desc.name);
	}

	void VFSNode::RemoveChild(usize index)
	{
		if (index >= m_children.size())
		{
			Log::Critical(LogType::VFS, "Index is bigger than the actual length of this node '{}'.", m_desc.name);
			return;
		}

		m_children.erase(m_children.begin() + index);
	}

	void VFSNode::ClearAll()
	{
		for (auto& child : m_children)
			child->ClearAll();
	}
}
