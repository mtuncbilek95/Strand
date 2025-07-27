/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>

namespace Flax
{
	class ObjectBase
	{
	public:
		virtual ~ObjectBase() = default;
	};

	struct FieldInfo
	{
		String fieldName;
		String typeName;
		usize typeHash;

		function<Any(void*)> getter;
		function<void(void*, const Any&)> setter;

		HashMap<String, Any> attirbutes;
	};

	struct ClassInfo
	{
		String className;
		usize size;

		function<Ref<ObjectBase>()> constructor;

		HashMap<String, FieldInfo> fields;
		HashMap<String, Any> attributes;
	};
}
