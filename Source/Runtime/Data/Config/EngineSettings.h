/*
 * Licensed under the terms specified in the LICENSE.md file
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>

namespace Strand
{
	struct GeneralSettings
	{
		String engineName;
		String engineVersion;
		u32 applicationType;

		GeneralSettings& setName(const String& name) { engineName = name; return *this; }
		GeneralSettings& setVersion(const String& version) { engineVersion = version; return *this; }
		GeneralSettings& setApplicationType(u32 type) { applicationType = type; return *this; }
	};

	struct GraphicsSettings
	{
		u32 graphicsAPI;
		u32 presentMode;
		u32 imageCount;
		u32 swapFormat;
		u32 depthFormat;
		u32 renderThreadCount;

		GraphicsSettings& setGraphicsAPI(u32 api) { graphicsAPI = api; return *this; }
		GraphicsSettings& setPresentMode(u32 mode) { presentMode = mode; return *this; }
		GraphicsSettings& setImageCount(u32 count) { imageCount = count; return *this; }
		GraphicsSettings& setSwapFormat(u32 format) { swapFormat = format; return *this; }
		GraphicsSettings& setDepthFormat(u32 format) { depthFormat = format; return *this; }
		GraphicsSettings& setRenderThreadCount(u32 count) { renderThreadCount = count; return *this; }
	};

	/**
	 * @struct EngineSettings
	 * @brief Structure for general engine settings for each instance of the engine.
	 */
	struct EngineSettings
	{
		GeneralSettings general;
		GraphicsSettings graphics;

		EngineSettings& setGeneral(const GeneralSettings& settings) { general = settings; return *this; }
		EngineSettings& setGraphics(const GraphicsSettings& settings) { graphics = settings; return *this; }

		static EngineSettings DefaultSettings()
		{
			EngineSettings engineSettings;
			engineSettings.setGeneral(
				GeneralSettings().setName("StrandEngine").setVersion("1.0.0").setApplicationType(0))
				.setGraphics(
					GraphicsSettings()
					.setGraphicsAPI(1)
					.setImageCount(2)
					.setPresentMode(2)
					.setSwapFormat(16)
					.setDepthFormat(30)
					.setRenderThreadCount(4));

			return engineSettings;
		}
	};
}
