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
#include <Runtime/Data/Delegate/Connection.h>

namespace Flax
{
	template<typename... Args>
	class Signal
	{
		using slotFunction = function<void(Args...)>;
		struct SlotData
		{
			SlotData(slotFunction s, usize i) : slot(s), id(i)
			{
			}

			slotFunction slot;
			usize id;
		};

	public:
		Connection Connect(slotFunction slot)
		{
			usize id = m_nextId++;
			m_slots.emplace_back(slot, id);

			return Connection([this, id]()
				{
					m_slots.erase(
						std::remove_if(m_slots.begin(), m_slots.end(),
							[id](const SlotData& slotData) { return slotData.id == id; }),
						m_slots.end());
				}
			)
		}

		template<typename T>
		Connection Connect(T&& func)
		{
			return Connect(slotFunction(std::forward<T>(func)));
		}

		template<typename T>
		Connection Connect(T* obj, void(T::* method)(Args...))
		{
			return Connect([obj, method](Args... args)
				{
					(obj->*method)(args...);
				});
		}

		void Emit(Args... args) 
		{
			auto slots_copy = m_slots;
			for (const auto& slot_data : slots_copy)
				slot_data.slot(args...);
		}
		void operator()(Args... args) { Emit(args...); }

		void DisconnectAll() { m_slots.clear(); }
		usize Count() const { return m_slots.size(); }

	private:
		Vector<SlotData> m_slots;
		usize m_nextId;
	};
}
