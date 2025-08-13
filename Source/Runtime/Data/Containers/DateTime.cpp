#include "DateTime.h"

#include <iostream>

namespace Strand
{
	DateTime::DateTime()
	{
		*this = GetCurrentDateTime();
	}

	DateTime::DateTime(const String& dateAsString)
	{
		std::tm t = {};

		std::istringstream ss(dateAsString);
		ss >> std::get_time(&t, "%d.%m.%Y %H:%M:%S");

		if (ss.fail()) {
			*this = GetCurrentDateTime();
			return;
		}

		m_day = static_cast<u8>(t.tm_mday);
		m_month = static_cast<u8>(t.tm_mon + 1);
		m_year = static_cast<u16>(t.tm_year + 1900);
		m_hour = static_cast<u8>(t.tm_hour);
		m_min = static_cast<u8>(t.tm_min);
		m_sec = static_cast<u8>(t.tm_sec);
	}

	DateTime::DateTime(u8 day, u8 month, u16 year, u8 hour, u8 min, u8 sec)
	{
		SetDateTime(day, month, year, hour, min, sec);
	}

	void DateTime::SetDay(u8 day)
	{
		if (!IsValidDate(day, m_month, m_year))
			throw std::invalid_argument("Invalid Day for the current Month/Year combination.");
		m_day = day;
	}

	void DateTime::SetMonth(u8 month)
	{
		if (!IsValidDate(m_day, month, m_year))
			throw std::invalid_argument("Invalid Month for the current Day/Year combination.");
		m_month = month;
	}

	void DateTime::SetYear(u16 year)
	{
		if (!IsValidDate(m_day, m_month, year))
			throw std::invalid_argument("Invalid Year for the current Day/Month combination.");
		m_year = year;
	}

	void DateTime::SetHour(u8 hour)
	{
		if (hour <= 23)
			m_hour = hour;
		else
			throw std::invalid_argument("Invalid Hour (0-23).");
	}

	void DateTime::SetMin(u8 min)
	{
		if (min <= 59)
			m_min = min;
		else
			throw std::invalid_argument("Invalid Minute (0-59).");
	}

	void DateTime::SetSec(u8 sec)
	{
		if (sec <= 59)
			m_sec = sec;
		else
			throw std::invalid_argument("Invalid Second (0-59).");
	}

	b8 DateTime::IsValidDate() const
	{
		return IsValidDate(m_day, m_month, m_year);
	}

	b8 DateTime::IsValidDate(u8 day, u8 month, u16 year)
	{
		if (year == 0)
			return false;
		if (month < 1 || month > 12)
			return false;
		if (day < 1 || day > DaysInMonth(month, year))
			return false;
		return true;
	}

	b8 DateTime::IsLeapYear() const
	{
		return IsLeapYear(m_year);
	}

	b8 DateTime::IsLeapYear(u16 year)
	{
		return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
	}

	u8 DateTime::DaysInMonth() const
	{
		return DaysInMonth(m_month, m_year);
	}

	u8 DateTime::DaysInMonth(u8 month, u16 year)
	{
		switch (month) 
		{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			return 31;
		case 4:
		case 6:
		case 9:
		case 11:
			return 30;
		case 2:
			return IsLeapYear(year) ? 29 : 28;
		default:
			throw std::invalid_argument("Invalid month for DaysInMonth.");
		}
	}

	String DateTime::ToString() const
	{
		std::ostringstream oss;
		oss << std::setw(2) << std::setfill('0') << m_day << '.'
			<< std::setw(2) << std::setfill('0') << m_month << '.'
			<< m_year << ' '
			<< std::setw(2) << std::setfill('0') << m_hour << ':'
			<< std::setw(2) << std::setfill('0') << m_min << ':'
			<< std::setw(2) << std::setfill('0') << m_sec;
		return oss.str();
	}

	b8 DateTime::operator==(const DateTime& other) const
	{
		return (m_year == other.m_year &&
			m_month == other.m_month &&
			m_day == other.m_day &&
			m_hour == other.m_hour &&
			m_min == other.m_min &&
			m_sec == other.m_sec);
	}

	b8 DateTime::operator<(const DateTime& other) const
	{
		if (m_year != other.m_year) return m_year < other.m_year;
		if (m_month != other.m_month) return m_month < other.m_month;
		if (m_day != other.m_day) return m_day < other.m_day;
		if (m_hour != other.m_hour) return m_hour < other.m_hour;
		if (m_min != other.m_min) return m_min < other.m_min;
		return m_sec < other.m_sec;
	}

	DateTime DateTime::GetCurrentDateTime()
	{
		std::time_t now = std::time(nullptr);
		std::tm* ltm = std::localtime(&now); // @XXX: not thread-safe -- @mateusdigital

		if (!ltm)
			throw std::runtime_error("Failed to get current local time.");

		return DateTime(
			static_cast<u8>(ltm->tm_mday),
			static_cast<u8>(ltm->tm_mon + 1),
			static_cast<u16>(ltm->tm_year + 1900),
			static_cast<u8>(ltm->tm_hour),
			static_cast<u8>(ltm->tm_min),
			static_cast<u8>(ltm->tm_sec)
		);
	}

	void DateTime::SetDateTime(u8 day, u8 month, u16 year, u8 hour, u8 min, u8 sec)
	{
		if (!IsValidDate(day, month, year))
			throw std::invalid_argument("Invalid date provided.");
		if (hour > 23 || min > 59 || sec > 59)
			throw std::invalid_argument("Invalid time provided.");

		m_day = day;
		m_month = month;
		m_year = year;
		m_hour = hour;
		m_min = min;
		m_sec = sec;
	}
}
