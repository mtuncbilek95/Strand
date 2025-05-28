/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Window/WindowContext.h>

namespace Flax
{
	class VContext;

	class Application
	{
	public:
		Application();
		~Application();

		void Run();

	private:
		Ref<BasicWindow> m_mainWindow;
		VContext* m_renderContext;
	};
}
