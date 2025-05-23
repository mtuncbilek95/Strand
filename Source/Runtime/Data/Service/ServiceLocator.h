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
#include <Runtime/Data/Logger/Logger.h>

namespace Flax
{
	class ServiceLocator
	{
	public:
		template<typename T>
		static void Register(Ref<T> service)
		{
			auto typeId = TypeIndex(typeid(T));
			Services()[typeId] = service;
		}

		template<typename T>
		static Ref<T> Get()
		{
			auto typeId = TypeIndex(typeid(T));

			auto it = Services().find(typeId);

			if (it == Services().end())
			{
				Log::Critical(LogType::IO, "Service '{}' ", typeId.name());
				return nullptr;
			}

			return std::static_pointer_cast<T>(it->second);
		}

	private:
		static HashMap<TypeIndex, Ref<void>>& Services()
		{
			static HashMap<TypeIndex, Ref<void>> instanceMap;
			return instanceMap;
		}
	};
}
