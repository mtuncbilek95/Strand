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

namespace Flax
{
	template<typename T>
	constexpr std::enable_if_t<std::is_enum_v<T>, T>
	operator|(T lhs, T rhs)
	{
		using Underlying = typename std::underlying_type_t<T>;
		return static_cast<T>(static_cast<Underlying>(lhs) | static_cast<Underlying>(rhs));
	}

    template<typename T>
    constexpr std::enable_if_t<std::is_enum_v<T>, T&>
        operator|=(T& lhs, T rhs)
    {
        using Underlying = std::underlying_type_t<T>;
        lhs = static_cast<T>(static_cast<Underlying>(lhs) | static_cast<Underlying>(rhs));
        return lhs;
    }

	template<typename T>
	constexpr std::enable_if_t<std::is_enum_v<T>, T>
		operator&(T lhs, T rhs) {
		using Underlying = typename std::underlying_type_t<T>;
		return static_cast<T>(static_cast<Underlying>(lhs) & static_cast<Underlying>(rhs));
	}

    template<typename T>
    constexpr std::enable_if_t<std::is_enum_v<T>, T&>
        operator&=(T& lhs, T rhs)
    {
        using Underlying = std::underlying_type_t<T>;
        lhs = static_cast<T>(static_cast<Underlying>(lhs) & static_cast<Underlying>(static_cast<Underlying>(rhs)));
        return lhs;
    }

    template<typename T>
    constexpr std::enable_if_t<std::is_enum_v<T>, T>
        operator~(T lhs)
    {
        using Underlying = std::underlying_type_t<T>;
        return static_cast<T>(~static_cast<Underlying>(lhs));
    }

	template<typename T>
	constexpr std::enable_if_t<std::is_enum_v<T>, b8>
		HasFlag(T lhs, T rhs)
	{
		using Underlying = typename std::underlying_type_t<T>;
		return (static_cast<Underlying>(lhs) & static_cast<Underlying>(rhs)) != 0;
	}

    template<typename T>
    constexpr std::enable_if_t<std::is_enum_v<T>, b8>
        IsSameFlag(T lhs, T rhs)
    {
        using Underlying = typename std::underlying_type_t<T>;
        return (static_cast<Underlying>(lhs) == static_cast<Underlying>(rhs));
    }

    template<typename T>
    constexpr std::enable_if_t<std::is_enum_v<T>, b8>
        operator==(T lhs, T rhs)
    {
        using Underlying = typename std::underlying_type_t<T>;
        return (static_cast<Underlying>(lhs) == static_cast<Underlying>(rhs));
    }

    template<typename T>
    constexpr std::enable_if_t<std::is_enum_v<T>, b8>
        operator!=(T lhs, T rhs)
    {
        using Underlying = typename std::underlying_type_t<T>;
        return (static_cast<Underlying>(lhs) != static_cast<Underlying>(rhs));
    }
}
