#include "ProjectConfig.h"

#include <magic_enum/magic_enum.hpp>

namespace Flax
{
	void ProjectConfig::LoadFrom(const String& projectPath)
	{
		FileStream stream(projectPath.data());
		if (!stream.is_open())
		{
			Log::Critical(LogType::IO, "Could not open '{}'", projectPath);
			exit(-1);
		}

		Json jsonFile;
		try 
		{
			stream >> jsonFile;

			m_desc.projectId = Uuid(jsonFile["projectDetails"]["projectId"].get<String>());
			m_desc.projectName = jsonFile["projectDetails"]["projectName"].get<String>();
			m_desc.engineVersion = Math::Vec3u(jsonFile["projectDetails"]["engineVersion"]["major"].get<u32>(),
				jsonFile["projectDetails"]["engineVersion"]["minor"].get<u32>(),
				jsonFile["projectDetails"]["engineVersion"]["patch"].get<u32>());
			m_desc.generateDate = DateTime();
			m_desc.lastModifiedDate = DateTime();
			m_desc.description = jsonFile["projectDetails"]["description"].get<String>();
			m_desc.graphicsApi = GfxType(jsonFile["projectDetails"]["graphicsApi"].get<u32>());
		}
		catch (const nlohmann::json::parse_error& e) 
		{
			Log::Error(LogType::IO, "JSON parse error: {}", e.what());
		}
		catch (const std::exception& e) 
		{
			Log::Error(LogType::IO, "An unexpected error occurred: {}", e.what());
		}

		stream.close();

		Log::Info(LogType::IO, "--- Project Configuration Details ---");
		Log::Info(LogType::IO, "  Project ID:        {}", m_desc.projectId.ToString());
		Log::Info(LogType::IO, "  Project Name:      {}", m_desc.projectName);
		Log::Info(LogType::IO, "  Engine Version:    {}.{}.{}", m_desc.engineVersion.x, m_desc.engineVersion.y, m_desc.engineVersion.z);
		Log::Info(LogType::IO, "  Generate Date:     {}", m_desc.generateDate.ToString());
		Log::Info(LogType::IO, "  Last Modified:     {}", m_desc.lastModifiedDate.ToString());
		Log::Info(LogType::IO, "  Description:       {}", m_desc.description);
		Log::Info(LogType::IO, "  Graphics API:      {}", magic_enum::enum_name<GfxType>(m_desc.graphicsApi));
		Log::Info(LogType::IO, "-----------------------------------");
	}

	void ProjectConfig::SaveFile()
	{
	}
}
