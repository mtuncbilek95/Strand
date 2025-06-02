/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Window/BasicWindow.h>

namespace Flax
{
	class WindowContext : public Singleton<WindowContext>
	{
		friend class Application;
	public:
		BasicWindow* CoreWindow() { return m_coreWindow.get(); }
		void CreateCoreWindow(const WindowProps& desc) { m_coreWindow = NewRef<BasicWindow>(desc); }

	private:
		void SetContextWindow(Ref<BasicWindow> window) { m_coreWindow = window; }

	private:
		Ref<BasicWindow> m_coreWindow;
	};
}
