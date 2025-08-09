/*
 * Licensed under the terms specified in the LICENSE.md file
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Data/Definitions/Definitions.h>
#include <Runtime/Data/Definitions/StdNames.h>

namespace Strand
{
	class Connection 
	{
	public:
		Connection() = default;
		Connection(voidFunc disconnect) : m_disconnectFunc(disconnect) {}
		~Connection()
		{
			m_disconnectFunc = nullptr;
		}

		void Disconnect()
		{
			if (m_disconnectFunc)
			{
				m_disconnectFunc();
				m_disconnectFunc = nullptr;
			}
		}

		b8 IsConnected() const { return m_disconnectFunc != nullptr; }

	private:
		voidFunc m_disconnectFunc;
	};
}
