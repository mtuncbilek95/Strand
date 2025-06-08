#include "VirtualFileSystem.h"

namespace Flax
{
	VirtualFileSystem::VirtualFileSystem(VFSType type, const String& rootPath)
	{
	}

	VirtualFileSystem::~VirtualFileSystem()
	{
	}

	void VirtualFileSystem::AddChild(const VFSNodeDesc& desc, VFSNode* pParent)
	{
	}

	void VirtualFileSystem::RemoveChild(const String& name, VFSNode* pParent)
	{
	}

	void VirtualFileSystem::RemoveChild(usize index, VFSNode* pParent)
	{
	}

	void VirtualFileSystem::Clear()
	{

	}

	VFSNode* VirtualFileSystem::Parent(const String& name, VFSNode* pParent) const
	{
		return nullptr;
	}

	VFSNode* VirtualFileSystem::Parent(usize index, VFSNode* pParent) const
	{
		return nullptr;
	}

	VFSNode* VirtualFileSystem::Node(const String& name, VFSNode* pParent) const
	{
		return nullptr;
	}

	VFSNode* VirtualFileSystem::Node(usize index, VFSNode* pParent) const
	{
		return nullptr;
	}

	usize VirtualFileSystem::Index(const String& name, VFSNode* pParent) const
	{
		return 0;
	}
}
