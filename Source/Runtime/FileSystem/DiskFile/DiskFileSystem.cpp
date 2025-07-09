#include "DiskFileSystem.h"

#include <Runtime/FileSystem/DiskFile/DiskFileNode.h>

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
			if (!FileSys::create_directories(fullPath.parent_path()))
			{
				Log::Error(LogType::FileSystem, "Failed to create file or directory '{}'.", fullPath.string());
				return;
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

		Log::Info(LogType::FileSystem, "Created file or directory '{}'.", fullPath.string());
	}

	void DiskFileSystem::Delete(const Path& virtualPath)
	{
	}

	void DiskFileSystem::Rename(const Path& oldVirtual, const Path& newVirtual)
	{
	}

	void DiskFileSystem::Copy(const Path& srcVirtual, const Path& dstVirtual)
	{
	}

	void DiskFileSystem::Move(const Path& srcVirtual, const Path& dstVirtual)
	{
	}

	Ref<IVirtualFileNode> DiskFileSystem::RootNode() const
	{
		return m_rootNode;
	}

	Ref<IVirtualFileNode> DiskFileSystem::Node(const Path& virtualPath) const
	{
		if (virtualPath.is_absolute())
		{
			Log::Critical(LogType::FileSystem, "Virtual path '{}' must not be absolute.", virtualPath.string());
			return nullptr;
		}

		Path fullPath = m_sourcePath / virtualPath;
		if (!FileSys::exists(fullPath))
		{
			Log::Error(LogType::FileSystem, "Virtual path '{}' does not exist.", virtualPath.string());
			return nullptr;
		}

		VirtualNodeDesc desc = VirtualNodeDesc().setName(fullPath.filename().string())
			.setVirtualPath(virtualPath)
			.setSourcePath(fullPath)
			.setType(FileSys::is_directory(fullPath) ? VirtualNodeType::Folder : VirtualNodeType::File);
		return NewRef<DiskFileNode>(desc, nullptr);
	}
}
