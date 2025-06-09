#include "LogReceiver.h"

namespace Flax
{
	LogReceiver* LogReceiver::Get()
	{
		static LogReceiver inst;
		return &inst;
	}
}
