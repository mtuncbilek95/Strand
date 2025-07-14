#include "RuntimeLoader.h"

#include <Runtime/FileSystem/Service/VirtualFileService.h>

#define TOML_EXCEPTIONS 0
#include <toml++/toml.h>

namespace Flax
{
	EngineSettings RuntimeLoader::LoadEngineSettings(const Path& path)
	{
		// Check if path !exists
		if (!FileSys::exists(path))
		{
			Log::Warn(LogType::Application, "Engine settings file '{}' does not exist. Using default settings.", path.string());

			// Get the injected path's folder line and create the route
			Path route = path.parent_path();
			if (FileSys::exists(route))
				Log::Info(LogType::Application, "Route exists just creating the config file.");
			else
			{
				Log::Warn(LogType::Application, "Route does not exist!");

				if (!FileSys::create_directories(route))
					Log::Error(LogType::Application, "Could not create the '{}'", route.string());
			}

			Log::Info(LogType::IO, "Created directories for engine settings at '{}'", route.string());

			// Get default settings
			EngineSettings defaultSettings = EngineSettings::DefaultSettings();

			Toml tbl;
			tbl.emplace("EngineSettings", Toml{
				{"General", Toml{
					{"EngineName", defaultSettings.general.engineName},
					{"EngineVersion", defaultSettings.general.engineVersion},
					{"EngineAuthor", "Neuvex IT & Consultancy"},
					{"ApplicationType", defaultSettings.general.applicationType}
				}},
				{"Graphics", Toml{
					{"GraphicsAPI", defaultSettings.graphics.graphicsAPI},
					{"PresentMode", defaultSettings.graphics.presentMode},
					{"ImageCount", defaultSettings.graphics.imageCount},
					{"ThreadCount", defaultSettings.graphics.renderThreadCount},
					{"SwapchainFormat", defaultSettings.graphics.swapFormat},
					{"DepthFormat", defaultSettings.graphics.depthFormat}
				}}
				});

			// Write it on EngineConfig.toml
			OutFileStream outputFile(path);
			if (outputFile.is_open())
			{
				outputFile << tbl;
				outputFile.close();
				Log::Info(LogType::IO, "Default engine settings saved to '{}'.", path.string());
			}
			else
				Log::Error(LogType::IO, "Failed to save default engine settings to '{}'. Check file permissions.", path.string());

			return defaultSettings;
		}

		// The engine config exists, use and take all the settings.
		toml::parse_result result = toml::parse_file(path.string());
		if (!result)
		{
			Log::Critical(LogType::IO, "Failed to parse engine settings from '{}': '{}'", path.string(), result.error().description());
			return EngineSettings::DefaultSettings();
		}

		Toml& tbl = result.table();
		Toml& general = *tbl["EngineSettings"]["General"].as_table();
		Toml& graphics = *tbl["EngineSettings"]["Graphics"].as_table();

		EngineSettings engineSettings;
		engineSettings.setGeneral(GeneralSettings().setName(general["EngineName"].value<String>().value())
			.setVersion(general["EngineVersion"].value<String>().value())
			.setApplicationType(general["ApplicationType"].value<u32>().value()))
			.setGraphics(GraphicsSettings().setGraphicsAPI(graphics["GraphicsAPI"].value<u32>().value())
				.setImageCount(graphics["ImageCount"].value<u32>().value())
				.setPresentMode(graphics["PresentMode"].value<u32>().value())
				.setSwapFormat(graphics["SwapchainFormat"].value<u32>().value())
				.setDepthFormat(graphics["DepthFormat"].value<u32>().value())
				.setRenderThreadCount(graphics["ThreadCount"].value<u32>().value()));

		return engineSettings;
	}

	ProjectSettings RuntimeLoader::LoadProjectSettings(const Path& path)
	{
		// Check 'Caches/ProjectSettings.toml'
		auto vfm = RuntimeService::Get<VirtualFileService>();
		
		if (!vfm->Exists(path))
		{
			Log::Error(LogType::Application, "'{}' does not exists. System will create new one!", path.string());

			vfm->Create(path);

			ProjectSettings defaultSettings = ProjectSettings().setDefaultScene("");
			
			Toml tbl;
			tbl.emplace("ProjectSettings", Toml{
				{"General", Toml{
					{ "DefaultScene", defaultSettings.defaultScene.string() }
				}}
				});

			OutFileStream outputFile(path);
			if (outputFile.is_open())
			{
				outputFile << tbl;
				outputFile.close();
				Log::Info(LogType::IO, "Default engine settings saved to '{}'.", path.string());
			}
			else
				Log::Error(LogType::IO, "Failed to save default engine settings to '{}'. Check file permissions.", path.string());

			return defaultSettings;
		}

		return ProjectSettings();
	}
}
