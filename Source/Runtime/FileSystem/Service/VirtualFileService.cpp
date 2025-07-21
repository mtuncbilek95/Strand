#include "VirtualFileService.h"

#include <Runtime/FileSystem/IVirtualFileSystem.h>
#include <Runtime/FileSystem/IVirtualFileNode.h>

namespace Flax
{
	void VirtualFileService::Initialize(const Path& sourcePath)
	{
		if (!sourcePath.is_absolute())
		{
			Log::Critical(LogType::FileSystem, "Source path '{}' must be absolute.", sourcePath.string());
			return;
		}

		if (!FileSys::is_directory(sourcePath))
		{
			Log::Critical(LogType::FileSystem, "Source path '{}' is not a directory.", sourcePath.string());
			return;
		}

		m_sourcePath = sourcePath;
	}

	void VirtualFileService::Mount(const Path& mountPoint, Ref<IVirtualFileSystem> fileSystem)
	{
		auto it = m_fileSystems.find(mountPoint.string());
		if (it != m_fileSystems.end())
			Log::Warn(LogType::FileSystem, "Mount point '{}' is already in use. Replacing existing file system.", mountPoint.string());

		m_fileSystems[mountPoint.string()] = fileSystem;

		fileSystem->Mount(mountPoint, m_sourcePath);
	}

	void VirtualFileService::Unmount(const Path& mountPoint)
	{
		auto it = m_fileSystems.find(mountPoint.string());
		if (it == m_fileSystems.end())
		{
			Log::Warn(LogType::FileSystem, "Mount point '{}' is not mounted.", mountPoint.string());
			return;
		}
		it->second->Unmount(Path(mountPoint));
		m_fileSystems.erase(it);
	}

	b8 VirtualFileService::Exists(const Path& path) const
	{
		Path targetPath = ClearMountPath(path);
		auto fileSystem = FileSystem(targetPath);

		if (!fileSystem)
		{
			Log::Critical(LogType::FileSystem, "File system for path '{}' is not found.", targetPath.string());
			return false;
		}

		return fileSystem->Exists(targetPath);
	}

	b8 VirtualFileService::IsDirectory(const Path& path) const
	{
		Path targetPath = ClearMountPath(path);
		auto fileSystem = FileSystem(targetPath);

		if (!fileSystem)
		{
			Log::Critical(LogType::FileSystem, "File system for path '{}' is not found.", targetPath.string());
			return false;
		}
		return fileSystem->IsDirectory(targetPath);
	}

	b8 VirtualFileService::IsFile(const Path& path) const
	{
		Path targetPath = ClearMountPath(path);
		auto fileSystem = FileSystem(targetPath);

		if (!fileSystem)
		{
			Log::Critical(LogType::FileSystem, "File system for path '{}' is not found.", targetPath.string());
			return false;
		}
		return fileSystem->IsFile(targetPath);
	}

	Path VirtualFileService::AbsolutePath(const Path& path) const
	{
		Path targetPath = ClearMountPath(path);
		auto fileSystem = FileSystem(targetPath);

		if (!fileSystem)
		{
			Log::Critical(LogType::FileSystem, "File system for path '{}' is not found.", targetPath.string());
			return Path();
		}

		return fileSystem->AbsolutePath(targetPath);
	}

	Path VirtualFileService::VirtualPath(const Path& path) const
	{
		Path targetPath = ClearMountPath(path);

		// Split source path from path
		if (!targetPath.is_absolute())
		{
			Log::Critical(LogType::FileSystem, "Virtual path '{}' must be absolute.", targetPath.string());
			return Path();
		}

		if (targetPath.empty())
		{
			Log::Critical(LogType::FileSystem, "Virtual path '{}' is empty.", targetPath.string());
			return Path();
		}

		Path relativePath = targetPath.lexically_relative(m_sourcePath);

		auto fileSystem = FileSystem(relativePath);
		if (!fileSystem)
		{
			Log::Critical(LogType::FileSystem, "File system for path '{}' is not found.", relativePath.string());
			return Path();
		}

		return fileSystem->Exists(relativePath) ? relativePath : Path();
	}

	void VirtualFileService::Refresh(const Path& path) const
	{
		auto filesystem = FileSystem(path);
		if (!filesystem)
		{
			Log::Critical(LogType::FileSystem, "File system for path '{}' is not found.", path.string());
			return;
		}

		auto node = filesystem->Node(path);
		if (!node)
		{
			Log::Critical(LogType::FileSystem, "Node for path '{}' is not found.", path.string());
			return;
		}

		node->Refresh();
	}

	void VirtualFileService::Create(const Path& path)
	{
		Path targetPath = ClearMountPath(path);
		auto fileSystem = FileSystem(targetPath);

		if (!fileSystem)
		{
			Log::Critical(LogType::FileSystem, "File system for path '{}' is not found.", targetPath.string());
			return;
		}

		if (fileSystem->Exists(targetPath))
		{
			Log::Warn(LogType::FileSystem, "File '{}' already exists.", targetPath.string());
			return;
		}

		fileSystem->Create(targetPath);
	}

	void VirtualFileService::Delete(const Path& path)
	{
		Path targetPath = ClearMountPath(path);
		auto fileSystem = FileSystem(targetPath);

		if (!fileSystem)
		{
			Log::Critical(LogType::FileSystem, "File system for path '{}' is not found.", targetPath.string());
			return;
		}

		if (!fileSystem->Exists(targetPath))
		{
			Log::Error(LogType::FileSystem, "File '{}' does not exist.", targetPath.string());
			return;
		}

		fileSystem->Delete(targetPath);
	}

	void VirtualFileService::Rename(const Path& oldPath, const Path& newPath)
	{
		Path oldTargetPath = ClearMountPath(oldPath);
		Path newTargetPath = ClearMountPath(newPath);
		auto fileSystem = FileSystem(oldTargetPath);
		
		if (!fileSystem)
		{
			Log::Critical(LogType::FileSystem, "File system for path '{}' is not found.", oldTargetPath.string());
			return;
		}

		if (!fileSystem->Exists(oldTargetPath))
		{
			Log::Warn(LogType::FileSystem, "File '{}' does not exist.", oldTargetPath.string());
			return;
		}

		if (fileSystem->Exists(newTargetPath))
		{
			Log::Warn(LogType::FileSystem, "File '{}' already exists.", newTargetPath.string());
			return;
		}

		fileSystem->Rename(oldTargetPath, newTargetPath);
	}

	void VirtualFileService::Copy(const Path& sourcePath, const Path& destinationPath)
	{
		Path sourceTargetPath = ClearMountPath(sourcePath);
		Path destinationTargetPath = ClearMountPath(destinationPath);
		auto fileSystem = FileSystem(sourceTargetPath);

		if (!fileSystem)
		{
			Log::Critical(LogType::FileSystem, "File system for path '{}' is not found.", sourceTargetPath.string());
			return;
		}
		
		if (!fileSystem->Exists(sourceTargetPath))
		{
			Log::Warn(LogType::FileSystem, "Source file '{}' does not exist.", sourceTargetPath.string());
			return;
		}
		
		if (fileSystem->Exists(destinationTargetPath))
		{
			Log::Warn(LogType::FileSystem, "Destination file '{}' already exists.", destinationTargetPath.string());
			return;
		}
		
		fileSystem->Copy(sourceTargetPath, destinationTargetPath);
	}

	void VirtualFileService::Move(const Path& sourcePath, const Path& destinationPath)
	{
		Path sourceTargetPath = ClearMountPath(sourcePath);
		Path destinationTargetPath = ClearMountPath(destinationPath);
		auto fileSystem = FileSystem(sourceTargetPath);
		
		if (!fileSystem)
		{
			Log::Critical(LogType::FileSystem, "File system for path '{}' is not found.", sourceTargetPath.string());
			return;
		}
		
		if (!fileSystem->Exists(sourceTargetPath))
		{
			Log::Warn(LogType::FileSystem, "Source file '{}' does not exist.", sourceTargetPath.string());
			return;
		}
		
		if (fileSystem->Exists(destinationTargetPath))
		{
			Log::Warn(LogType::FileSystem, "Destination file '{}' already exists.", destinationTargetPath.string());
			return;
		}
		
		fileSystem->Move(sourceTargetPath, destinationTargetPath);
	}

	void VirtualFileService::InitializeServiceField()
	{
	}

	void VirtualFileService::ResetServiceField()
	{
		m_fileSystems.clear();
		m_sourcePath.clear();
	}

	Path VirtualFileService::ClearMountPath(const Path& path) const
	{
		String pathStr = path.string();

		while (!pathStr.empty() && (pathStr[0] == '/' || pathStr[0] == '\\'))
			pathStr.erase(0, 1);

		return Path(pathStr);
	}

	Ref<IVirtualFileSystem> VirtualFileService::FileSystem(const Path& path) const
	{
		if (path.empty())
		{
			Log::Critical(LogType::FileSystem, "Path '{}' is empty.", path.string());
			return nullptr;
		}

		auto it = path.begin();
		if (it == path.end())
			throw std::runtime_error("Target path is invalid.");

		String mountKey = it->string();

		auto fsIt = m_fileSystems.find(mountKey);
		if (fsIt == m_fileSystems.end())
		{
			Log::Critical(LogType::FileSystem, "Mount point '{}' is not mounted.", mountKey);
			return nullptr;
		}

		return fsIt->second;
	}

	Ref<IVirtualFileNode> VirtualFileService::Node(const Path& virtPath)
	{
		return nullptr;
	}

	struct VirtualFileSystemRegister
	{
		VirtualFileSystemRegister() { RuntimeService::Register(NewRef<VirtualFileService>()); }
	};
	static VirtualFileSystemRegister gb_virtualFileSystemRegister;
}
