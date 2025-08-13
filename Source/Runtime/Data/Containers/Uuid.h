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
    /*
     * @class Uuid
     * @brief Custom unique universal id.
     */
	class Uuid final
	{
		friend struct UuidHash;
		friend struct UuidHelper;
	public:
		Uuid() = default;
		~Uuid() = default;

		Uuid(u32 a, u16 b, u16 c, u64 d);
		Uuid(const Uuid& other);
		Uuid(const String& str);

		u32 GetA() const { return m_a; }
		u16 GetB() const { return m_b; }
		u16 GetC() const { return m_c; }
		u64 GetD() const { return m_d; }

		String ToString() const;

		b8 operator==(const Uuid& other) const;
		b8 operator!=(const Uuid& other) const;

	private:
		u32 m_a = {};
		u16 m_b = {};
		u16 m_c = {};
		u64 m_d = {};
	};

	struct UuidHash
	{
		usize operator()(const Uuid& other) const;
	};

	struct UuidHelper
	{
		UuidHelper() = delete; // Makes a static class
		static Uuid GenerateID();
	};
}
