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
#include <Runtime/Serialization/TypeInfo.h>

namespace Flax
{
	/**
	 * @class MethodInfo
	 * @brief This class is a method reflect structure for runtime 
	 * reflection system. We will be able to reflect our functions, so
	 * we can use/manipulate or functions in editor time. 
	 * 
	 * E.g - 1: We can write functions for material graph system. Then
	 * we can create some node system with a more generalized approach.
	 * Whenever we bind nodes inside of the material system. It can gather
	 * every information from nodes one by one and handle shaders. We can
	 * even bind this structure with our custom shaders and use it inside 
	 * of the material graph.
	 * 
	 * E.g - 2: Game modders can access those functions and create their
	 * mods for the games that made with the engine.
	 */
	struct MethodInfo
	{
		String methodName;
		u32 methodHash;
		TypeInfo trailType;

		Vector<TypeInfo> parameters;
		void* (*methodPtr)(void*, void*);
	};
}
