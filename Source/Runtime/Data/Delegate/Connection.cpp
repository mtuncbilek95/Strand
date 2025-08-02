#include "Connection.h"

namespace Strand
{
	Connection::Connection(voidFunc disconnect) : m_disconnectFunc(disconnect)
	{
	}

	void Connection::Disconnect()
	{
		if (m_disconnectFunc)
		{
			m_disconnectFunc();
			m_disconnectFunc = nullptr;
		}
	}

	b8 Connection::IsConnected() const 
	{
		return m_disconnectFunc != nullptr;
	}
}
