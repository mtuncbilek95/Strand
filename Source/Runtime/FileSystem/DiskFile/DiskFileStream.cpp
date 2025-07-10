#include "DiskFileStream.h"

namespace Flax
{
	DiskFileStream::DiskFileStream(const Path& filePath, FileMode mode)
	{
		IosBase::openmode openMode = GetOpenMode(mode);
		m_stream.open(filePath, openMode);

		if (!m_stream.is_open())
		{
			Log::Error(LogType::FileSystem, "Failed to open file: {}", filePath.string());
			return;
		}
		else
		{
			m_stream.seekg(0, IosBase::end);
			m_size = m_stream.tellg();
			m_stream.seekg(0, IosBase::beg);
		}
	}

	DiskFileStream::~DiskFileStream()
	{
		Close();
	}

	usize DiskFileStream::Read(c8* buffer, usize size)
	{
		if (!m_stream.is_open() || m_stream.bad()) return 0;
		m_stream.read(buffer, size);
		return m_stream.gcount();
	}

	usize DiskFileStream::Write(const c8* buffer, usize size)
	{
		if (!m_stream.is_open() || m_stream.bad()) return 0;
		m_stream.write(buffer, size);
		return size;
	}

	usize DiskFileStream::Seek(usize offset, i32 origin)
	{
		if (!m_stream.is_open())
			return u64_max;

		m_stream.seekg(offset, GetSeekDir(origin));
		m_stream.seekp(offset, GetSeekDir(origin));

		if (m_stream.fail())
		{
			Log::Error(LogType::FileSystem, "Failed to seek in file: {}", m_filePath.string());
			return u64_max;
		}

		return 0;
	}

	usize DiskFileStream::Tell() const
	{
		if (!m_stream.is_open())
			return u64_max;

		return 0;
	}

	b8 DiskFileStream::IsEof() const
	{
		return m_stream.eof();
	}

	b8 DiskFileStream::HasError() const
	{
		return m_stream.fail() || m_stream.bad();
	}

	void DiskFileStream::Close()
	{
		if (m_stream.is_open())
			m_stream.close();
	}

	usize DiskFileStream::Size() const
	{
		return m_size;
	}

	IosBase::openmode DiskFileStream::GetOpenMode(FileMode mode) const
	{
		switch (mode)
		{
		case FileMode::Read:
			return IosBase::in;
		case FileMode::Write:
			return IosBase::out | IosBase::trunc;
		case FileMode::Append:
			return IosBase::out | IosBase::app;
		case FileMode::Binary:
			return IosBase::binary;
		default:
			return IosBase::in;
		}
	}

	SeekDir DiskFileStream::GetSeekDir(i32 origin) const
	{
		switch (origin)
		{
		case 0:
			return std::ios_base::beg;
		case 1:
			return std::ios_base::cur;
		case 2:
			return std::ios_base::end;
		default:
			return std::ios_base::beg;
		}
	}
}
