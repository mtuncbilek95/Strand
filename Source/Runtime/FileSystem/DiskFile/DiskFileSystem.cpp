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

	Path DiskFileSystem::AbsolutePath(const Path& virtPath) const
	{
		if (virtPath.is_absolute())
		{
			Log::Critical(LogType::FileSystem, "Virtual path '{}' must not be absolute.", virtPath.string());
			return Path();
		}

		Path fullPath = m_sourcePath / virtPath;
		return FileSys::absolute(fullPath);
	}

	Path DiskFileSystem::VirtualPath(const Path& absolutePath) const
	{
		if (!absolutePath.is_absolute())
		{
			Log::Critical(LogType::FileSystem, "Absolute path '{}' must be absolute.", absolutePath.string());
			return Path();
		}

		Path relativePath = absolutePath.lexically_relative(m_sourcePath);
		if (relativePath.empty())
		{
			Log::Critical(LogType::FileSystem, "Virtual path for '{}' is empty.", absolutePath.string());
			return Path();
		}
		return relativePath;
	}

	void DiskFileSystem::Create(const Path& virtPath)
	{
		if (virtPath.is_absolute())
		{
			Log::Critical(LogType::FileSystem, "Virtual path '{}' must not be absolute.", virtPath.string());
			return;
		}

		Path fullPath = m_sourcePath / virtPath;
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

		auto node = FindNodeInTree(virtPath.parent_path());
		if (node)
			node->Refresh();
	}

	void DiskFileSystem::Delete(const Path& virtPath)
	{
		if (virtPath.is_absolute())
		{
			Log::Critical(LogType::FileSystem, "Virtual path '{}' must not be absolute.", virtPath.string());
			return;
		}

		Path fullPath = m_sourcePath / virtPath;
		if (!FileSys::exists(fullPath))
		{
			Log::Warn(LogType::FileSystem, "File or directory '{}' does not exist.", fullPath.string());
			return;
		}
		
		if (FileSys::is_directory(fullPath))
		{
			if (!FileSys::remove_all(fullPath))
			{
				Log::Error(LogType::FileSystem, "Failed to delete directory '{}'.", fullPath.string());
				return;
			}
		}
		else
		{
			if (!FileSys::remove(fullPath))
			{
				Log::Error(LogType::FileSystem, "Failed to delete file '{}'.", fullPath.string());
				return;
			}
		}
		
		auto node = FindNodeInTree(virtPath.parent_path());
		if (node)
			node->Refresh();
	}

	void DiskFileSystem::Rename(const Path& oldVirtual, const Path& newVirtual)
	{
		Path srcFullPath = ToRealPath(oldVirtual);
		Path dstFullPath = ToRealPath(newVirtual);

		if (srcFullPath.is_absolute() || dstFullPath.is_absolute())
		{
			Log::Critical(LogType::FileSystem, "Virtual paths '{}' and '{}' must not be absolute.", oldVirtual.string(), newVirtual.string());
			return;
		}

		if (srcFullPath.empty() || dstFullPath.empty())
		{
			Log::Critical(LogType::FileSystem, "Virtual paths '{}' and '{}' must not be empty.", oldVirtual.string(), newVirtual.string());
			return;
		}

		if (!FileSys::exists(srcFullPath))
		{
			Log::Warn(LogType::FileSystem, "Source path '{}' does not exist.", srcFullPath.string());
			return;
		}

		if (FileSys::exists(dstFullPath))
		{
			Log::Warn(LogType::FileSystem, "Destination path '{}' already exists.", dstFullPath.string());
			return;
		}

		FileSys::rename(srcFullPath, dstFullPath);
	}

	void DiskFileSystem::Copy(const Path& srcVirtual, const Path& dstVirtual)
	{
		Log::Warn(LogType::FileSystem, "NOT IMPLEMENTED YET!");
	}

	void DiskFileSystem::Move(const Path& srcVirtual, const Path& dstVirtual)
	{
		Log::Warn(LogType::FileSystem, "NOT IMPLEMENTED YET!");
	}

	Ref<IVirtualFileNode> DiskFileSystem::Node(const Path& virtPath) const
	{
		return FindNodeInTree(virtPath);
	}

	Ref<IFileStream> DiskFileSystem::Open(const Path& virtualPath, FileMode mode)
	{
		return nullptr;
	}

	Ref<DiskFileNode> DiskFileSystem::FindNodeInTree(const Path& virtPath) const
	{
		if (virtPath == m_mountPoint)
			return m_rootNode;

		Path relativePath = virtPath.lexically_relative(m_mountPoint);
		String pathStr = relativePath.string();

		Vector<String> segments;
		for (const auto& segment : relativePath)
			segments.emplace_back(segment.string());

		Ref<DiskFileNode> currNode = m_rootNode;
		for (const String& segment : segments)
		{
			if (segment.empty())
				continue;

			if (!currNode->IsFolder())
				return nullptr;

			currNode->Refresh();

			auto tempNode = currNode->Child(segment);
			if (!tempNode)
			{
				Log::Critical(LogType::FileSystem, "Node '{}' not found in the virtual file system.", pathStr);
				return nullptr;
			}
			else
				currNode = std::static_pointer_cast<DiskFileNode>(tempNode);
		}

		return currNode;
	}

	Path DiskFileSystem::ToRealPath(const Path& virtPath) const
	{
		if (virtPath.is_absolute())
		{
			Log::Critical(LogType::FileSystem, "Virtual path '{}' must not be absolute.", virtPath.string());
			return Path();
		}

		if (virtPath.empty())
		{
			Log::Critical(LogType::FileSystem, "Virtual path is empty.");
			return Path();
		}

		return m_sourcePath / virtPath;
	}
}
