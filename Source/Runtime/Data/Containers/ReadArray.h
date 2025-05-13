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
    class ReadArray
    {
    public:
        using iterator = T*;
        using const_iterator = const T*;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    public:
        ReadArray() noexcept : m_data(nullptr), m_size(0) {}
        ReadArray(usize size) : m_data(MakeBuffer(size)), m_size(size) 
        {
            for (usize i = 0; i < size; ++i)
                new (&m_data[i]) T();
        }

        ReadArray(const T* data, usize size) : m_data(MakeBuffer(size)), m_size(size)
        {
            for (usize i = 0; i < size; ++i)
                new (&m_data[i]) T(data[i]);
        }

        ReadArray(const InitList<T>& list) : m_data(MakeBuffer(list.size())), m_size(list.size())
        {
            i32 i = 0;
            for (const T& item : list)
                new (&m_data[i++]) T(item);
        }

        ReadArray(const ReadArray& other) : m_data(MakeBuffer(other.m_size)), m_size(other.m_size)
        {
            for (usize i = 0; i < m_size; ++i)
                new (&m_data[i]) T(other.m_data[i]);
        }

        ReadArray(ReadArray&& other) noexcept : m_data(other.m_data), m_size(other.m_size)
        {
            other.m_data = nullptr;
            other.m_size = 0;
        }

        ReadArray(const Vector<T>& vect) : m_data(MakeBuffer(vect.size())), m_size(vect.size())
        {
            for (usize i = 0; i < m_size; ++i)
                new (&m_data[i]) T(vect[i]);
        }

        ReadArray(usize size, const T& value) : m_data(MakeBuffer(size)), m_size(size)
        {
            for (usize i = 0; i < size; ++i)
                new (&m_data[i]) T(value);
        }

        template<typename... Args>
        ReadArray(usize size, Args&&... args) : m_data(MakeBuffer(size)), m_size(size)
        {
            for (usize i = 0; i < size; ++i)
                new (&m_data[i]) T(std::forward<Args>(args)...);
        }

        ~ReadArray()
        {
            ClearData();
            ::operator delete(m_data);
        }

        ReadArray& operator=(const ReadArray& rhs)
        {
            if (this == &rhs)
                return *this;

            Resize(rhs.m_size);

            for (usize i = 0; i < m_size; ++i)
                new (&m_data[i]) T(rhs[i]);
            return *this;
        }

        ReadArray& operator=(const InitList<T>& list)
        {
            Resize(list.size());
            i32 i = 0;
            for (const T& item : list)
                new (&m_data[i++]) T(item);
            return *this;
        }

        ReadArray& operator=(ReadArray<T>&& rhs) noexcept
        {
            if (this == &rhs)
                return *this;

            ClearData();
            ::operator delete(m_data);

            m_data = rhs.m_data;
            m_size = rhs.m_size;
            rhs.m_data = nullptr;
            rhs.m_size = 0;
            
            return *this;
        }

        ReadArray& operator=(const Vector<T>& vect)
        {
            Resize(vect.size());
            for (usize i = 0; i < m_size; ++i)
                new (&m_data[i]) T(vect[i]);
            return *this;
        }

        T& operator[](usize index) noexcept { return m_data[index]; }
        const T& operator[](usize index) const noexcept { return m_data[index]; }
        T* Data() noexcept { return m_data; }
        const T* Data() const noexcept { return m_data; }

        b8 Empty() const noexcept { return m_size == 0; }
        usize Size() const noexcept { return m_size; }
        usize SizeInBytes() const noexcept { return m_size * sizeof(T); }

        operator bool() const noexcept { return m_data; }

        iterator begin() noexcept { return m_data; }
        const_iterator begin() const noexcept { return m_data; }
        iterator end() noexcept { return m_data + m_size; }
        const_iterator end() const noexcept { return m_data + m_size; }
        reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
        const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
        reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
        const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }

    private:
        T* MakeBuffer(usize size) { return static_cast<T*>(::operator new(sizeof(T) * size)); }
        
        void ClearData() 
        {
            if constexpr (!std::is_trivially_destructible_v<T>)
            {
                // Call the destructor on all the members in reverse order
                for (size_t i = m_size; i > 0;)
                    m_data[--i].~T();
            }
        }
        
        void Resize(usize size) 
        {
            ClearData();
            if (m_size != size)
            {
                ::operator delete(m_data);
                m_data = MakeBuffer(size);
                m_size = size;
            }

            for (usize i = 0; i < m_size; ++i)
                new (&m_data[i]) T();
        }

    private:
        T* m_data;
        usize m_size;
    };
}