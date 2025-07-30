/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Data/Definitions/Definitions.h>
#include <Runtime/Data/Definitions/StdNames.h>

namespace Flax
{
	class Connection 
	{
	public:
		Connection() = default;
		Connection(voidFunc disconnect);

		void SetConnection(voidFunc disconnect);
		
		void Disconnect();
		b8 IsConnected() const;

	private:
		voidFunc m_disconnectFunc = {};
	};
}
