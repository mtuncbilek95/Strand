#include "FileSystem.h"

namespace Flax
{
	void FileSystem::SetRootPath(const Path& path)
	{
		// Check if the path is empty
		if (path.empty())
		{
			Log::Critical(LogType::FileSystem, "Root path for FileSystem cannot be empty.");
			exit(-1);
		}

		// Check if the path is file path
		if (path.has_filename())
		{
			Log::Critical(LogType::FileSystem, "Root path for FileSystem cannot be a file path: {}", path.string());
			exit(-1);
		}

		// Check if the root path is absolute
		if (!path.is_absolute())
		{
			Log::Critical(LogType::FileSystem, "Root path for FileSystem must be absolute.");
			exit(-1);
		}

		// Check if the root path exists
		if (!Exists(path))
		{
			Log::Critical(LogType::FileSystem, "Root path for FileSystem does not exist: {}", path.string());
			exit(-1);
		}

		// Set the root path
		m_rootPath = path;
	}

	const Path& FileSystem::RootPath() const
	{
		return m_rootPath;
	}

	void FileSystem::NewDirectory(const Path& path)
	{
		// Check if the directory already exists
		if (Exists(path))
		{
			Log::Warn(LogType::FileSystem, "Directory already exists: {}", path.string());
			return;
		}

		if (path.is_absolute())
		{
			// Create the directory as absolute with all parent directories
			if (!FileSys::create_directories(path))
			{
				Log::Error(LogType::FileSystem, "Failed to create directory: {}", path.string());
				exit(-1);
			}
		}
		else
		{
			// Create the directory as relative with all parent directories
			Path absolutePath = m_rootPath / path;

			if (!FileSys::create_directories(absolutePath))
			{
				Log::Error(LogType::FileSystem, "Failed to create directory: {}", absolutePath.string());
				exit(-1);
			}
		}
	}

	void FileSystem::DeleteDirectory(const Path& path)
	{
		// Check if the directory exists
		if (!Exists(path) || !IsDirectory(path))
		{
			Log::Error(LogType::FileSystem, "Directory does not exist: {}", path.string());
			return;
		}

		// Remove the directory and all its contents
		try
		{
			FileSys::remove_all(path);
		}
		catch (const FileSys::filesystem_error& e)
		{
			Log::Error(LogType::FileSystem, "Failed to delete directory: {}. Error: {}", path.string(), e.what());
			exit(-1);
		}
	}

	void FileSystem::NewFile(const Path& path)
	{
		// Check if the file already exists
		if (Exists(path))
		{
			Log::Warn(LogType::FileSystem, "File already exists: {}", path.string());
			return;
		}

		Path absolutePath;
		// If the path is absolute, create the file directly
		if (path.is_absolute())
			absolutePath = path;
		else
			absolutePath = m_rootPath / path;

		// Create the parent directories if they do not exist
		if (!FileSys::exists(absolutePath.parent_path()))
		{
			if (!FileSys::create_directories(absolutePath.parent_path()))
			{
				Log::Error(LogType::FileSystem, "Failed to create parent directories for file: {}", absolutePath.string());
				exit(-1);
			}
		}

		// Create the file
		try
		{
			std::ofstream file(absolutePath, std::ios::out | std::ios::trunc);
			if (!file)
			{
				Log::Error(LogType::FileSystem, "Failed to create file: {}", absolutePath.string());
				exit(-1);
			}
			file.close();
		}
		catch (const std::ofstream::failure& e)
		{
			Log::Error(LogType::FileSystem, "Failed to create file: {}. Error: {}", absolutePath.string(), e.what());
			exit(-1);
		}
	}

	void FileSystem::RemoveFile(const Path& path)
	{
		// Check if the file exists
		if (!Exists(path) || !IsFile(path))
		{
			Log::Error(LogType::FileSystem, "File does not exist: {}", path.string());
			return;
		}

		Path absolutePath;
		// If the path is absolute, remove the file directly
		if (path.is_absolute())
			absolutePath = path;
		else
			absolutePath = m_rootPath / path;

		try
		{
			FileSys::remove(absolutePath);
		}
		catch (const FileSys::filesystem_error& e)
		{
			Log::Error(LogType::FileSystem, "Failed to remove file: {}. Error: {}", absolutePath.string(), e.what());
			exit(-1);
		}
	}

	void FileSystem::RenameFile(const Path& oldPath, const Path& newPath)
	{
		// Check if the old file exists
		if (!Exists(oldPath) || !IsFile(oldPath))
		{
			Log::Error(LogType::FileSystem, "Old file does not exist: {}", oldPath.string());
			return;
		}

		Path absoluteOldPath;
		// If the old path is absolute, use it directly
		if (oldPath.is_absolute())
			absoluteOldPath = oldPath;
		else
			absoluteOldPath = m_rootPath / oldPath;

		Path absoluteNewPath;
		// If the new path is absolute, use it directly
		if (newPath.is_absolute())
			absoluteNewPath = newPath;
		else
			absoluteNewPath = m_rootPath / newPath;
		try
		{
			FileSys::rename(absoluteOldPath, absoluteNewPath);
		}
		catch (const FileSys::filesystem_error& e)
		{
			Log::Error(LogType::FileSystem, "Failed to rename file from {} to {}. Error: {}", absoluteOldPath.string(), absoluteNewPath.string(), e.what());
			exit(-1);
		}
	}

	void FileSystem::DuplicateFile(const Path& sourcePath, const Path& destinationPath)
	{

	}

	void FileSystem::RouteFile(const Path& sourcePath, const Path& destinationPath)
	{
	}

	b8 FileSystem::Exists(const Path& path) const
	{
		Path absolutePath;
		// If the path is absolute, use it directly
		if (path.is_absolute())
			absolutePath = path;
		else
			absolutePath = m_rootPath / path;

		return FileSys::exists(absolutePath);
	}

	b8 FileSystem::IsDirectory(const Path& path) const
	{
		Path absolutePath;
		// If the path is absolute, use it directly
		if (path.is_absolute())
			absolutePath = path;
		else
			absolutePath = m_rootPath / path;

		return FileSys::is_directory(absolutePath);
	}

	b8 FileSystem::IsFile(const Path& path) const
	{
		Path absolutePath;
		// If the path is absolute, use it directly
		if (path.is_absolute())
			absolutePath = path;
		else
			absolutePath = m_rootPath / path;

		return FileSys::is_regular_file(absolutePath);
	}

	Path FileSystem::SeparatePathFromRoot(const Path& path) const
	{
		if (!path.is_absolute())
			return path;

		if (path.has_filename())
		{
			auto rootPath = m_rootPath;
			if (path.string().find(rootPath.string()) == 0)
				return path.lexically_relative(rootPath);
			else
			{
				Log::Error(LogType::FileSystem, "Path {} is not under the root path {}", path.string(), rootPath.string());
				return Path();
			}
		}
		else
		{
			Log::Error(LogType::FileSystem, "Path does not have a filename: {}", path.string());
			return Path();
		}

	}

	Path FileSystem::ExtractPath(const Path& path) const
	{
		return Path();
	}

	String FileSystem::ExtractFileName(const Path& path) const
	{
		if (path.has_filename())
			return path.filename().string();
		else
		{
			Log::Error(LogType::FileSystem, "Path does not have a filename: {}", path.string());
			return String();
		}
	}

	String FileSystem::ExtractExtension(const Path& path) const
	{
		if (path.has_extension())
			return path.extension().string();
		else
		{
			Log::Error(LogType::FileSystem, "Path does not have an extension: {}", path.string());
			return String();
		}
	}

	String FileSystem::ExtractFileWExt(const Path& path) const
	{
		if (path.has_filename())
			return path.stem().string();
		else
		{
			Log::Error(LogType::FileSystem, "Path does not have a filename: {}", path.string());
			return String();
		}
	}

	void FileSystem::ResetServiceField()
	{
		m_rootPath.clear();
	}

	struct FileSystemRegister
	{
		FileSystemRegister() { RuntimeService::Register<FileSystem>(NewRef<FileSystem>()); }
	};
	static FileSystemRegister gb_fileSystemRegister;
}
