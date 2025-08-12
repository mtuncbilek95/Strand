/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Data/Definitions/Definitions.h>
#include <Runtime/Data/Definitions/StdNames.h>
#include <Runtime/Data/Containers/Singleton.h>
#include <Runtime/Logger/Logger.h>
#include <Runtime/Reflection/TypeAccessor.h>
#include <Runtime/Reflection/ReflectionRegistry.h>
#include <Runtime/Reflection/IReflectable.h>

namespace Strand
{
#define STRAND_OBJECT(ClassName) \
	private: \
		friend class TypeAccessor<ClassName>; \
	public: \
		static String StaticClassName() \
		{ \
			return #ClassName; \
		} \
		virtual ClassInfo* GetClass() const override \
		{ \
			return ReflectionRegistry::Get().GetClassInfo<ClassName>(); \
		} \
	private:

#define STRAND_CLASS(...)
#define STRAND_ENUM(...)
#define STRAND_FIELD(...)
#define STRAND_METHOD(...)
}