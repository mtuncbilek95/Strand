#include "RuntimeLoader.h"

#define TOML_EXCEPTIONS 0
#include <toml++/toml.h>

namespace Flax
{
	EngineSettings RuntimeLoader::LoadEngineSettings(const String& path)
	{
		if (!FileSystem::exists(Path(path)))
		{
			Log::Warn(LogType::IO, "Engine settings file '{}' does not exist. Using default settings.", path);

			Path route = Path(path).parent_path();
			if (FileSystem::create_directories(route))
			{
				Log::Info(LogType::IO, "Created directories for engine settings at '{}'", route.string());

				EngineSettings defaultSettings = EngineSettings::DefaultSettings();

				toml::table tbl;
				tbl.emplace("EngineSettings", toml::table{
					{"General", toml::table{
						{"EngineName", defaultSettings.general.engineName},
						{"EngineVersion", defaultSettings.general.engineVersion},
						{"EngineAuthor", "Neuvex IT & Consultancy"}
					}},
					{"Graphics", toml::table{
						{"GraphicsAPI", defaultSettings.graphics.graphicsAPI},
						{"PresentMode", defaultSettings.graphics.presentMode},
						{"ImageCount", defaultSettings.graphics.imageCount},
						{"ThreadCount", defaultSettings.graphics.renderThreadCount},
						{"SwapchainFormat", defaultSettings.graphics.swapFormat},
						{"DepthFormat", defaultSettings.graphics.depthFormat}
					}}
					});

				std::ofstream outputFile(path);
				if (outputFile.is_open()) 
				{
					outputFile << tbl;
					outputFile.close();
					Log::Info(LogType::IO, "Default engine settings saved to '{}'.", path);
				}
				else
					Log::Error(LogType::IO, "Failed to save default engine settings to '{}'. Check file permissions.", path);

				return defaultSettings;
			}

			return EngineSettings::DefaultSettings();
		}

		toml::parse_result result = toml::parse_file(path);

		if (!result)
		{
			Log::Critical(LogType::IO, "Failed to parse engine settings from '{}': '{}'", path, result.error().description());
			return EngineSettings::DefaultSettings();
		}

		toml::table& tbl = result.table();
		toml::table& general = *tbl["EngineSettings"]["General"].as_table();
		toml::table& graphics = *tbl["EngineSettings"]["Graphics"].as_table();
		
		EngineSettings engineSettings;
		engineSettings.setGeneral(GeneralSettings().setName(general["EngineName"].value<String>().value())
			.setVersion(general["EngineVersion"].value<String>().value()))
			.setGraphics(GraphicsSettings().setGraphicsAPI(graphics["GraphicsAPI"].value<u32>().value())
				.setImageCount(graphics["ImageCount"].value<u32>().value())
				.setPresentMode(graphics["PresentMode"].value<u32>().value())
				.setSwapFormat(graphics["SwapchainFormat"].value<u32>().value())
				.setDepthFormat(graphics["DepthFormat"].value<u32>().value())
				.setRenderThreadCount(graphics["ThreadCount"].value<u32>().value()));

		return engineSettings;
	}
}
