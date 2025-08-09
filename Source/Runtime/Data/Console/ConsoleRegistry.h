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
	/**
	 * @class ConsoleRegistry
	 * @brief This class is to catch console commands and execute them 
	 * for any properties. E.g. user can type something like
	 * "graphics.setWireframeEnabled true" in console and this may
	 * enable the wireframes onto the regular mesh representation.
	 */
	class ConsoleRegistry : public Singleton<ConsoleRegistry>
	{
	public:
		void RegisterCommand(const String& commandCall, voidFunc&& func) {}
		void ExecuteCommand(const String& command, const String& value) {}

	private:
		HashMap<String, function<void(const String&)>> m_commands;
	};
}
