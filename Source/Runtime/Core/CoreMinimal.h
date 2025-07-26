/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
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

#define RUNTIME_NOT_IMPLEMENTED_YET(returnType) \
	{ \
		Log::Error(LogType::Engine, "'{}' This function is not implemented yet!", __FUNCTION__); \
		return returnType; \
	}
