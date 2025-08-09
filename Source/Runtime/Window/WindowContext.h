/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Window/BasicWindow.h>

namespace Strand
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
