/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>

namespace Flax
{
	class BasicWindow;
	class ProceduralSkyPipeline;
	class IrradiancePipeline;
	class SkyPass;

	class Application
	{
	public:
		Application();
		~Application();

		void Run(); 

	private:
		Ref<BasicWindow> m_mainWindow;

		Ref<ProceduralSkyPipeline> m_skyPipeline;
		Ref<IrradiancePipeline> m_irradiancePipeline;
		Ref<SkyPass> m_skyPass;
	};
}
