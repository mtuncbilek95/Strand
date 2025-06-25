#include "VirtualFileSystem.h"

#include <Runtime/VirtualFile/VFSNode.h>

namespace Flax
{
	VirtualFileSystem::VirtualFileSystem(VFSType type, const String& rootPath) : m_type(type), 
		m_rootPath(rootPath)
	{
		m_rootNode = NewRef<VFSNode>(VFSNodeDesc({ "root", VFSNodeType::Directory }));
	}

	VirtualFileSystem::~VirtualFileSystem()
	{
	}

	void VirtualFileSystem::AddNode(const String& name, VFSNodeType type, VFSNode* pParent)
	{
		if (!pParent)
			pParent = m_rootNode.get();

		VFSNodeDesc desc = VFSNodeDesc()
			.setName(name)
			.setType(type);

		pParent->AddChild(desc);
	}

	void VirtualFileSystem::RemoveNode(VFSNode* pChild, VFSNode* pParent)
	{
		if (!pParent)
			pParent = m_rootNode.get();

		if (!pChild)
			pParent->ClearAll();

		pParent->RemoveChild(pParent);
	}

	usize VirtualFileSystem::CountOf(const String& name, VFSNode* pParent)
	{
		if (!pParent)
			pParent = m_rootNode.get();

		VFSNode* node = pParent->Find(name);
		return node->Count();
	}

	VFSNode* VirtualFileSystem::FindNode(const String& name, VFSNode* pParent)
	{
		if (!pParent)
			pParent = m_rootNode.get();

		return pParent->Find(name);
	}

	String VirtualFileSystem::AbsolutePath(VFSNode* pTarget)
	{
		if (!pTarget)
			pTarget = m_rootNode.get();

		Vector<String> parts;

		while (pTarget && pTarget != m_rootNode.get())
		{
			parts.push_back(pTarget->Name());
			pTarget = pTarget->Parent();
		}

		String actualPath = m_rootPath;
		for (auto it = parts.rbegin(); it != parts.rend(); ++it)
			actualPath += "/" + *it;

		return actualPath;
	}

	String VirtualFileSystem::AbsolutePath(const String& nodeName)
	{
		VFSNode* node = FindNodeRecursive(m_rootNode.get(), nodeName);
		if (node)
			return AbsolutePath(node);

		Log::Error(LogType::VFS, "Could not find the path of '{}'", nodeName);
		return String();
	}

	VFSNode* VirtualFileSystem::FindNodeRecursive(VFSNode* node, const String& name)
	{
		if (!node)
			return nullptr;

		if (node->Name() == name)
			return node;

		for (auto& child : node->Children())
		{
			if (auto* result = FindNodeRecursive(child.get(), name))
				return result;
		}

		return nullptr;
	}
}
