#include "VFSNode.h"

namespace Flax
{
	VFSNode::VFSNode(const VFSNodeDesc& desc, VFSNode* pParent) : m_desc(desc), 
		m_parent(pParent)
	{
	}

	VFSNode::~VFSNode()
	{
		for (auto& child : m_children)
		{
			if (child->m_parent == this)
				child->m_parent = nullptr;
		}
		m_children.clear();
	}

	void VFSNode::AddChild(const String& name, VFSNodeType type)
	{
		if (name.empty())
		{
			Log::Error(LogType::VFS, "VFSNode::AddChild: Cannot add a child with an empty name to '{}'", m_desc.name);
			return;
		}
		if (Find(name))
		{
			Log::Error(LogType::VFS, "VFSNode::AddChild: Node '{}' already exists in '{}'", name, m_desc.name);
			return;
		}
		AddChild(Ref<VFSNode>(new VFSNode({ name, type }, this)));
	}

	void VFSNode::AddChild(Ref<VFSNode> node)
	{
		if (!node)
		{
			Log::Error(LogType::VFS, "VFSNode::AddChild: Cannot add a null node to '{}'", m_desc.name);
			return;
		}

		if (node->m_parent)
		{
			Log::Error(LogType::VFS, "VFSNode::AddChild: Node '{}' already has a parent '{}'", node->Name(), node->m_parent->Name());
			return;
		}

		node->m_parent = this;
		m_children.push_back(std::move(node));
	}

	void VFSNode::RemoveChild(const String& name)
	{
		for (usize i = 0; i < m_children.size(); ++i)
		{
			if (m_children[i]->Name() == name)
			{
				m_children.erase(m_children.begin() + i);
				return;
			}
		}
		Log::Error(LogType::VFS, "VFSNode::RemoveChild: Node '{}' not found in '{}'", name, m_desc.name);
	}

	void VFSNode::RemoveChild(VFSNode* node)
	{
		for (usize i = 0; i < m_children.size(); ++i)
		{
			if (m_children[i].get() == node)
			{
				m_children.erase(m_children.begin() + i);
				return;
			}
		}
		Log::Error(LogType::VFS, "VFSNode::RemoveChild: Node '{}' not found in '{}'", node->Name(), m_desc.name);
	}

	void VFSNode::RemoveChild(const Ref<VFSNode>& node)
	{
		for (usize i = 0; i < m_children.size(); ++i)
		{
			if (m_children[i] == node)
			{
				m_children.erase(m_children.begin() + i);
				return;
			}
		}

		Log::Error(LogType::VFS, "VFSNode::RemoveChild: Node '{}' not found in '{}'", node->Name(), m_desc.name);
	}

	void VFSNode::ClearAll()
	{
		for (auto& child : m_children)
			child->ClearAll();

		m_children.clear();
	}

	String VFSNode::RelativePath() const
	{
		String path = m_desc.name;

		VFSNode* current = m_parent;
		while (current)
		{
			path = current->m_desc.name + "/" + path;
			current = current->m_parent;
		}

		return path;
	}

	VFSNode* VFSNode::Find(const String& name) const
	{
		for(usize i = 0; i < m_children.size(); ++i)
		{
			if (m_children[i]->Name() == name)
				return m_children[i].get();
		}

		Log::Error(LogType::VFS, "VFSNode::Find: Node '{}' not found in '{}'", name, m_desc.name);
		return nullptr;
	}

	VFSNode* VFSNode::Find(usize index) const
	{
		if (index >= m_children.size())
			return nullptr;

		return m_children[index].get();
	}
}
