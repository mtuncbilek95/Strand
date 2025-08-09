/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Data/Definitions/Definitions.h>
#include <Runtime/Data/Definitions/StdNames.h>
#include <Runtime/Logger/Logger.h>
#include <Runtime/Service/Service.h>

namespace Strand
{
	class ServiceLocator
	{
	public:
		template<typename T, typename = std::enable_if_t<std::is_base_of_v<Service, T>>>
		static void Register(Ref<T> service)
		{
			auto typeId = UniqueTypeId<T>();
			Services()[typeId] = service;

			Log::Debug(LogType::IO, "Service '{}' registered successfully.", typeid(T).name());
		}

		template<typename T>
		static Ref<T> Get()
		{
			auto typeId = UniqueTypeId<T>();
			auto it = Services().find(typeId);

			if (it == Services().end())
				Register<T>(NewRef<T>());

			it = Services().find(typeId);
			return std::static_pointer_cast<T>(it->second);
		}

		static void InitializeServices()
		{
			auto& sVices = Services();

			for (auto& el : sVices)
				el.second->InitializeServiceField();
		}

		static void ClearServices()
		{
			auto& sVices = Services();

			for (auto& el : sVices)
				el.second->ResetServiceField();

			sVices.clear();
		}

	private:
		static HashMap<i32, Ref<Service>>& Services()
		{
			static HashMap<i32, Ref<Service>> instanceMap;
			return instanceMap;
		}
	};
}
