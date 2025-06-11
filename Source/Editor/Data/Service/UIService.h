/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Editor/Data/Service/UIServiceBase.h>

namespace Flax
{
	class UIService
	{
	public:
		template<typename T, typename = std::enable_if_t<std::is_base_of_v<UIServiceBase, T>>>
		static void Register(T* pService = nullptr)
		{
			TypeIndex typeId = TypeIndex(typeid(T));
			Services()[typeId] = pService ? pService : new T();
			Log::Info(LogType::Editor, "Registered service: {}", TypeIndex(typeid(T)).name());
		}

		template<typename T>
		static T* Get()
		{
			TypeIndex typeId = TypeIndex(typeid(T));
			auto it = Services().find(typeId);
			if (it != Services().end())
				return qobject_cast<T*>(it->second);

			return nullptr;
		}

	private:
		static HashMap<TypeIndex, UIServiceBase*>& Services()
		{
			static HashMap<TypeIndex, UIServiceBase*> instanceMap;
			return instanceMap;
		}
	};
}
