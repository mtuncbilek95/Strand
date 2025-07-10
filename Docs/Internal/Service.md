# Service System

Almost every manager run through the service system. The service system is a singleton that manages the lifecycle of the managers. 
The service registry works as initialization at point of definition. So in order to connect a manager to the service system, you 
need to register it to service registry within the source file as below.

```cpp
// ExampleService.h

#pragma once

#include <Runtime/Core/CoreMinimal.h>

namespace Flax
{
	class ExampleService : public RuntimeServiceBase
	{
	public:
		ExampleService() = default;
		~ExampleService() = default;
		
		void DoSomething() const;
		void ResetServiceField() override final;
	}
}
```

```cpp
// ExampleService.cpp

#include "ExampleService.h"

namespace Flax
{
	void ExampleService::DoSomething() const
	{
		Log::Debug(LogType::Service, "ExampleService -- I'm doing something with debug!");
	}

	void ExampleService::ResetServiceField()
	{
		// You can clear your fields in here. Runtime service will call it.
	}

	struct ExampleServiceRegister
	{
		ExampleServiceRegister() { RuntimeService::Register(NewRef<ExampleService>()); }
	}
	static ExampleServiceRegister gb_exampleServiceRegister;
}
```

```cpp
// Usage in main

#include <Scripts/Example/Service/ExampleService.h>

using namespace Flax;

int main(i32 argC, c8** argV)
{
	auto service = RuntimeService::Get<ExampleService>();
	service->DoSomething();

	return 0;
}
```