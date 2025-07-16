#include "DiskFileSystem.h"

#include <Runtime/FileSystem/DiskFile/DiskFileNode.h>
#include <Runtime/FileSystem/DiskFile/DiskFileStream.h>

namespace Flax
{
	void DiskFileSystem::Mount(const Path& mountPoint, const Path& sourcePath)
	{
		if (!sourcePath.is_absolute())
		{
			Log::Critical(LogType::FileSystem, "Source path '{}' must be absolute.", sourcePath.string());
			return;
		}

		if (mountPoint.is_absolute())
		{
			Log::Critical(LogType::FileSystem, "Mount point '{}' must not be absolute.", mountPoint.string());
			return;
		}

		if (!FileSys::exists(sourcePath) || !FileSys::exists(sourcePath / mountPoint))
		{
			Log::Critical(LogType::FileSystem, "Source path '{}' does not exist.", sourcePath.string());
			return;
		}

		if (!FileSys::is_directory(sourcePath))
		{
			Log::Critical(LogType::FileSystem, "Source path '{}' is not a directory.", sourcePath.string());
			return;
		}

		m_sourcePath = sourcePath;
		m_mountPoint = mountPoint;

		VirtualNodeDesc desc = VirtualNodeDesc().setName(m_mountPoint.string())
			.setVirtualPath(m_mountPoint)
			.setSourcePath(m_sourcePath / m_mountPoint)
			.setType(VirtualNodeType::Folder);

		m_rootNode = NewRef<DiskFileNode>(desc, nullptr);
		m_rootNode->Refresh();

		Log::Info(LogType::FileSystem, "Mounted disk file system from '{}' to '{}'.", sourcePath.string(), mountPoint.string());
	}

	void DiskFileSystem::Unmount(const Path& mountPoint)
	{
		if (m_mountPoint != mountPoint)
		{
			Log::Critical(LogType::FileSystem, "Mount point '{}' does not match the current mount point '{}'.", mountPoint.string(), m_mountPoint.string());
			return;
		}

		m_sourcePath.clear();
		m_mountPoint.clear();
		m_rootNode.reset();
		m_rootNode = nullptr;
		Log::Info(LogType::FileSystem, "Unmounted disk file system from '{}'.", mountPoint.string());
	}

	Ref<IFileStream> DiskFileSystem::Open(const Path& virtualPath, FileMode mode)
	{
		Path realPath = ToRealPath(virtualPath);

		if (!FileSys::is_regular_file(realPath))
		{
			Log::Error(LogType::FileSystem, "File '{}' is not a regular file.", virtualPath.string());
			return nullptr;
		}

		if (!FileSys::exists(realPath))
		{
			Log::Error(LogType::FileSystem, "File '{}' does not exist.", virtualPath.string());
			return nullptr;
		}

		return NewRef<DiskFileStream>(realPath, mode);
	}

	b8 DiskFileSystem::Exists(const Path& path) const
	{
		if (path.is_absolute())
		{
			Log::Critical(LogType::FileSystem, "Path '{}' must not be absolute.", path.string());
			return false;
		}

		Path fullPath = m_sourcePath / path;
		return FileSys::exists(fullPath);
	}

	b8 DiskFileSystem::IsDirectory(const Path& path) const
	{
		if (path.is_absolute())
		{
			Log::Critical(LogType::FileSystem, "Path '{}' must not be absolute.", path.string());
			return false;
		}
		Path fullPath = m_sourcePath / path;
		return FileSys::is_directory(fullPath);
	}

	b8 DiskFileSystem::IsFile(const Path& path) const
	{
		if (path.is_absolute())
		{
			Log::Critical(LogType::FileSystem, "Path '{}' must not be absolute.", path.string());
			return false;
		}

		Path fullPath = m_sourcePath / path;
		return FileSys::is_regular_file(fullPath);
	}

	Path DiskFileSystem::AbsolutePath(const Path& virtualPath) const
	{
		if(virtualPath.is_absolute())
		{
			Log::Critical(LogType::FileSystem, "Virtual path '{}' must not be absolute.", virtualPath.string());
			return Path();
		}

		Path fullPath = m_sourcePath / virtualPath;
		return FileSys::absolute(fullPath);
	}

	void DiskFileSystem::Create(const Path& virtualPath)
	{
		if (virtualPath.is_absolute())
		{
			Log::Critical(LogType::FileSystem, "Virtual path '{}' must not be absolute.", virtualPath.string());
			return;
		}

		Path fullPath = m_sourcePath / virtualPath;
		if (FileSys::exists(fullPath))
		{
			Log::Warn(LogType::FileSystem, "File or directory '{}' already exists.", fullPath.string());
			return;
		}

		// If the path is a file, ensure the parent directory created/existed first
		if (!FileSys::is_directory(fullPath))
		{
			if (!FileSys::exists(fullPath.parent_path()))
			{
				if (!FileSys::create_directories(fullPath.parent_path()))
				{
					Log::Error(LogType::FileSystem, "Failed to create file or directory '{}'.", fullPath.string());
					return;
				}
			}

			if (fullPath.has_filename())
				OutFileStream(fullPath).close();
		}
		else // If the path is a directory, ensure it exists
		{
			if (!FileSys::create_directories(fullPath))
			{
				Log::Error(LogType::FileSystem, "Failed to create file or directory '{}'.", fullPath.string());
				return;
			}
		}

		Ref<DiskFileNode> currentNode = m_rootNode;
		if (!currentNode)
		{
			Log::Error(LogType::FileSystem, "DiskFileSystem root node is not initialized for mount point '{}'.", m_mountPoint.string());
			return;
		}

		Vector<String> segments;
		for (const auto& segment : virtualPath)
		{
			if (segment == m_mountPoint.string())
				continue;
			segments.push_back(segment.string());
		}

		Path currentVirtualSegmentPath = m_mountPoint;
		for (size_t i = 0; i < segments.size(); ++i)
		{
			const String& segment = segments[i];
			if (segment.empty())
				continue;

			currentVirtualSegmentPath /= segment;
			Ref<IVirtualFileNode> foundChild = nullptr;

			if (currentNode->IsFolder())
			{
				currentNode->Refresh();

				for (usize j = 0; j < currentNode->Count(); ++j)
				{
					Ref<IVirtualFileNode> child = currentNode->Child(j);
					if (child && child->Name() == segment)
					{
						foundChild = child;
						break;
					}
				}
			}

			if (foundChild)
				currentNode = std::dynamic_pointer_cast<DiskFileNode>(foundChild);
			else
			{
				Log::Error(LogType::FileSystem, "Consistency error: Node '{}' not found after refresh in '{}'.", segment, currentNode->VirtualPath().string());
				return;
			}
		}

		Log::Info(LogType::FileSystem, "Created file or directory '{}'.", fullPath.string());
	}

	void DiskFileSystem::Delete(const Path& virtualPath)
	{
		Log::Warn(LogType::FileSystem, "NOT IMPLEMENTED YET!");
	}

	void DiskFileSystem::Rename(const Path& oldVirtual, const Path& newVirtual)
	{
		Log::Warn(LogType::FileSystem, "NOT IMPLEMENTED YET!");
	}

	void DiskFileSystem::Copy(const Path& srcVirtual, const Path& dstVirtual)
	{
		Log::Warn(LogType::FileSystem, "NOT IMPLEMENTED YET!");
	}

	void DiskFileSystem::Move(const Path& srcVirtual, const Path& dstVirtual)
	{
		Log::Warn(LogType::FileSystem, "NOT IMPLEMENTED YET!");
	}

	Ref<IVirtualFileNode> DiskFileSystem::RootNode() const
	{
		return m_rootNode;
	}

	Ref<IVirtualFileNode> DiskFileSystem::Node(const Path& virtualPath) const
	{
		return FindNodeInTree(virtualPath);
	}

	Ref<DiskFileNode> DiskFileSystem::FindNodeInTree(const Path& virtualPath) const
	{
		String absPathStr = virtualPath.string();
		String mountPointStr = m_mountPoint.string();

		if (absPathStr.rfind(mountPointStr, 0) != 0)
		{
			Log::Error(LogType::FileSystem, "Path '{}' is not part of this file system's mount point '{}'.", virtualPath.string(), m_mountPoint.string());
			return nullptr;
		}

		if (virtualPath == m_mountPoint)
			return m_rootNode;

		Path relativeToMountPoint = virtualPath.lexically_relative(m_mountPoint);
		Ref<DiskFileNode> currentNode = m_rootNode;

		if (!currentNode)
		{
			Log::Error(LogType::FileSystem, "DiskFileSystem root node is not initialized for mount point '{}'.", m_mountPoint.string());
			return nullptr;
		}

		Vector<String> segments;
		for (const auto& segment : relativeToMountPoint)
			segments.push_back(segment.string());

		for (const String& segment : segments)
		{
			if (segment.empty())
				continue;

			Ref<IVirtualFileNode> foundChild = nullptr;

			if (!currentNode->IsFolder())
			{
				Log::Warn(LogType::FileSystem, "Cannot traverse into a non-directory node: '{}'. Path segment: '{}'", currentNode->VirtualPath().string(), segment);
				return nullptr;
			}

			currentNode->Refresh();

			for (usize i = 0; i < currentNode->Count(); ++i)
			{
				Ref<IVirtualFileNode> child = currentNode->Child(i);
				if (child && child->Name() == segment)
				{
					foundChild = child;
					break;
				}
			}

			if (foundChild)
				currentNode = std::static_pointer_cast<DiskFileNode>(foundChild);
			else
			{
				Log::Warn(LogType::FileSystem, "Node for segment '{}' not found under '{}'. Path: '{}'", segment, currentNode->VirtualPath().string(), virtualPath.string());
				return nullptr;
			}
		}
		return currentNode;
	}

	Path DiskFileSystem::ToRealPath(const Path& virtualPath) const
	{
		if (virtualPath.is_absolute())
		{
			Log::Critical(LogType::FileSystem, "Virtual path '{}' must not be absolute.", virtualPath.string());
			return Path();
		}

		if (virtualPath.empty())
		{
			Log::Critical(LogType::FileSystem, "Virtual path is empty.");
			return Path();
		}

		return m_sourcePath / virtualPath;
	}

	Path DiskFileSystem::ToVirtualPath(const Path& realPath) const
	{
		if (!realPath.is_absolute())
		{
			Log::Critical(LogType::FileSystem, "Real path '{}' must be absolute.", realPath.string());
			return Path();
		}

		if (realPath.empty())
		{
			Log::Critical(LogType::FileSystem, "Real path is empty.");
			return Path();
		}

		if (realPath.string().find(m_sourcePath.string()) != 0)
		{
			Log::Critical(LogType::FileSystem, "Real path '{}' is not under the source path '{}'.", realPath.string(), m_sourcePath.string());
			return Path();
		}
		
		Path relativePath = realPath.lexically_relative(m_sourcePath);
		if (relativePath.empty())
		{
			Log::Critical(LogType::FileSystem, "Real path '{}' is not under the source path '{}'.", realPath.string(), m_sourcePath.string());
			return Path();
		}

		return relativePath;
	}
}
