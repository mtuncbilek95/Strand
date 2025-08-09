/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Input/InputEvent.h>

namespace Strand
{
	class InputDispatcher : public Service
	{
		using EventCallback = function<void(const InputEvent&)>;

	public:
		void RegisterListener(WindowPollEvent type, EventCallback callback);
		void DispatchEvent(const InputEvent& event);

		void InitializeServiceField() override final {}
		void ResetServiceField() override final {}

	private:
		HashMap<WindowPollEvent, Vector<EventCallback>> m_listeners;
	};
}