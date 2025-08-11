/*
 * Licensed under the terms specified in the LICENSE.md file
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Data/Definitions/Definitions.h>
#include <Runtime/Data/Definitions/StdNames.h>
#include <Runtime/Reflection/TypeInfo.h>

namespace Strand
{
	/**
	 * @class FieldInfo
	 * @brief Defines the fields of a struct or class one by one inside
	 * of the runtime reflection system.
	 *
	 * E.g - 1: We can use FieldInfo to set MeshRendererComponent's Mesh
	 * in EditorTime and it can be automatically set. So we can see our
	 * decisions without coding.
	 */
	struct FieldInfo
	{
		String fieldName;
		TypeInfo fieldTypeInfo;
		usize offset; // Offset inside of the class

		template<typename T>
		T* GetValue(void* instance) const
		{
			return reinterpret_cast<T*>((char*)instance + offset);
		}

		template<typename T>
		void SetValue(void* instance, const T& value) const
		{
			*reinterpret_cast<T*>((char*)instance + offset) = value;
		}

		void SetValue(void* instance, const void* source) const
		{
			memcpy((char*)instance + offset, source, fieldTypeInfo.typeSize);
		}

		/*template<typename T>
		T& GetValue(void* instance) const { return *reinterpret_cast<T*>(c8*)instance + offset); }
		template<typename T>
		void SetValue(void* instance, const T& value) const { *reinterpret_cast<T*>((char*)instance + offset) = value; }
		void SetValue(void* instance, const void* source) const { memcpy((char*)instance + offset, source, fieldTypeInfo.typeSize); }*/
	};
}
