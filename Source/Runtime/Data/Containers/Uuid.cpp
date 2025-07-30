#include "Uuid.h"

#include <format>

#if defined(FLAX_WINDOWS)
#include <objbase.h>
#endif

namespace Flax
{
	Uuid::Uuid(u32 a, u16 b, u16 c, u64 d) : m_a(a), m_b(b), m_c(c), m_d(d)
	{
	}

	Uuid::Uuid(const Uuid& other) : m_a(other.m_a), m_b(other.m_b), m_c(other.m_c), m_d(other.m_d)
	{
	}

    Uuid::Uuid(const String& str) : m_a(0), m_b(0), m_c(0), m_d(0)
    {
        m_a = std::stoul(str.substr(0, 8), nullptr, 16);
        m_b = static_cast<u16>(std::stoul(str.substr(9, 4), nullptr, 16));
        m_c = static_cast<u16>(std::stoul(str.substr(14, 4), nullptr, 16));

        u16 low = static_cast<u16>(std::stoul(str.substr(19, 4), nullptr, 16));
        u64 high = std::stoull(str.substr(24, 12), nullptr, 16);
        m_d = (high << 16) | low;
    }


	String Uuid::ToString() const
	{
		char buffer[64];
		std::snprintf(buffer, sizeof(buffer), "%08x-%04x-%04x-%04x-%012llx", m_a, m_b, m_c, (u16)m_d, m_d >> 16);
		return buffer;
	}

	b8 Uuid::operator==(const Uuid& other) const
	{
		return other.m_a == m_a && other.m_b == m_b && other.m_c == m_c && other.m_d == m_d;
	}

	b8 Uuid::operator!=(const Uuid& other) const
	{
		return !(other == *this);
	}

	usize UuidHash::operator()(const Uuid& other) const
	{
        return static_cast<usize>(std::hash<u64>{}(other.m_d));
	}

    Uuid UuidHelper::GenerateID()
    {
#if defined(FLAX_WINDOWS)
		Uuid guid = {};
		HRESULT hr = CoCreateGuid((GUID*)(&guid.m_a));
		return guid;
#endif
    }
}
