/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Input/InputEvent.h>

namespace Flax
{
	class InputDispatcher
	{
		using EventCallback = function<void(const InputEvent&)>;

	public:
		void RegisterListener(WindowPollEvent type, EventCallback callback);
		void DispatchEvent(const InputEvent& event);
	private:
		HashMap<WindowPollEvent, Vector<EventCallback>> m_listeners;
	};
}