/*
 * Licensed under the terms specified in the LICENSE.md file
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Data/Containers/ReadArray.h>
#include <Runtime/Data/Containers/Uuid.h>
#include <Runtime/Data/Containers/Singleton.h>
#include <Runtime/Data/Containers/DateTime.h>

#include <Runtime/Data/Definitions/Definitions.h>
#include <Runtime/Data/Definitions/StdHelpers.h>
#include <Runtime/Data/Definitions/BitwiseOperator.h>
#include <Runtime/Data/Definitions/TypeTraits.h>

#include <Runtime/Data/Tools/DataReader.h>
#include <Runtime/Service/ServiceLocator.h>

#include <Runtime/Logger/Logger.h>

#include <Runtime/Data/Definitions/StdNames.h>
#include <Runtime/Data/Definitions/GlmNames.h>
#include <Runtime/Data/Definitions/JsonNames.h>

#include <Runtime/Platform/PlatformPath.h>

#include <Runtime/Reflection/Reflection.h>

#define RUNTIME_NOT_IMPLEMENTED_YET(returnType) \
	{ \
		Log::Error(LogType::Engine, "'{}' This function is not implemented yet!", __FUNCTION__); \
		return returnType; \
	}
