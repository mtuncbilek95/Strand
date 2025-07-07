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
	/**
	 * @class DateTime
	 * @brief Represents a date and time value.
	 */
	class DateTime
	{
	public:
		DateTime();
		DateTime(const String& dateAsString);
		DateTime(u8 day, u8 month, u16 year, u8 hour = 0, u8 min = 0, u8 sec = 0);

		DateTime(const DateTime& other) = default;
		DateTime(DateTime&& other) noexcept = default;
		DateTime& operator=(const DateTime& other) = default;
		DateTime& operator=(DateTime&& other) noexcept = default;

		~DateTime() = default;

		u8 Day() const { return m_day; }
		u8 Month() const { return m_month; }
		u16 Year() const { return m_year; }
		u8 Hour() const { return m_hour; }
		u8 Min() const { return m_min; }
		u8 Sec() const { return m_sec; }

		void SetDay(u8 day);
		void SetMonth(u8 month);
		void SetYear(u16 year);
		void SetHour(u8 hour);
		void SetMin(u8 min);
		void SetSec(u8 sec);

		b8 IsValidDate() const;
		static b8 IsValidDate(u8 day, u8 month, u16 year);
		b8 IsLeapYear() const;
		static b8 IsLeapYear(u16 year);
		u8 DaysInMonth() const;
		static u8 DaysInMonth(u8 month, u16 year);
		String ToString() const;

		b8 operator==(const DateTime& other) const;
		b8 operator!=(const DateTime& other) const { return !(*this == other); }
		b8 operator<(const DateTime& other) const;
		b8 operator<=(const DateTime& other) const { return (*this < other) || (*this == other); }
		b8 operator>(const DateTime& other) const { return !(*this <= other); }
		b8 operator>=(const DateTime& other) const { return !(*this < other); }

		DateTime operator+(int days) const;
		DateTime& operator+=(int days);

		static DateTime GetCurrentDateTime();

	private:
		void SetDateTime(u8 day, u8 month, u16 year, u8 hour, u8 min, u8 sec);

	private:
		u8 m_day;
		u8 m_month;
		u16 m_year;
		u8 m_hour;
		u8 m_min;
		u8 m_sec;

	};
}
