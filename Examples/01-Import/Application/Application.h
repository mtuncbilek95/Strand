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
	class Scene;

	class Application
	{
	public:
		Application(i32 argC, c8** argV);
		~Application();

		void Run();

	private:
		Ref<Scene> m_scene;
	};
}

