/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Data/Definitions/Definitions.h>
#include <Runtime/Data/Definitions/StdNames.h>

namespace Strand
{
	enum class TypeCategory
	{
		Signed8,		// i8
		Signed16,		// i16
		Signed32,		// i32
		Signed64,		// i64
		Unsigned8,		// u8
		Unsigned16,		// u16
		Unsigned32,		// u32
		Unsigned64,		// u64 || usize
		Float32,		// f32
		Float64,		// f64
		Boolean,		// b8
		Char,			// c8
		String,			// String
		Class,			// class
		Struct,			// struct
		Enum,			// Enum
		Pointer		 	// *
	};

	/**
	 * @class TypeInfo
	 * @brief Core information for runtime reflection system. TypeInfo
	 * should be able to define every type of the primitives we can have
	 * in our runtime system. So if we design a new class which will be used
	 * only as fields but should be reflectable, will send its information
	 * via TypeInfo into the runtime reflection system.
	 */
	struct TypeInfo
	{
		String typeName;
		u32 typeHash;
		usize typeSize;
		TypeCategory category;
	};
}
