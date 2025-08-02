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
#include <Runtime/Reflection/TypeInfo.h>
#include <Runtime/Reflection/FieldInfo.h>

namespace Strand
{
	 /**
	 * @class ConstructorInfo
	 * @brief Defines all the constructors' information that belongs
	 * to the class in the runtime reflection.
	 */
	struct ConstructorInfo
	{
		u32 parameterHash;
		Vector<TypeInfo> parameterTypes;
		function<void* (const void* const*)> constructorPtr;
	};

	/**
	 * @class ClassInfo
	 * @brief Runtime reflection's class information. Reflection
	 * structure will fill this struct and we will use ClassInfo
	 * within Meta Serialization, Editor Components' Serialization and
	 * Editor Components' data selection system. 
	 * E.g - 1: defining a mesh object for MeshRendererComponent in 
	 * editor side.
	 * E.g - 2: Using JsonSerializer with easier approach for each
	 * asset file in the engine runtime.
	 * E.g - 3: Creating ECS components with more generalized methods.
	 */
	struct ClassInfo
	{
		String className;
		u32 classHash;
		usize classSize;
		usize classAlignment;

		Vector<ConstructorInfo> constructors;
		HashMap<u32, usize> constructorLookup;

		String firstSuperClass;
		Vector<String> superClassNames;

		HashMap<String, FieldInfo> fields;
	};
}
