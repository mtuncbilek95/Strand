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
	class ViewModelBase;

	class ViewModelRegistry : public Singleton<ViewModelRegistry>
	{
	public:
		template<typename T, typename = std::enable_if_t<std::is_base_of_v<ViewModelBase, T>>>
		void RegisterVM()
		{
			QString name = T::staticMetaObject.className();

			Ref<T> viewModel = NewRef<T>();
			m_registry.insert(name, viewModel);
			Log::Debug(LogType::Editor, "'{}' has been registered to ViewModelRegistry.", name.toStdString());
		}

		template<typename T, typename = std::enable_if_t<std::is_base_of_v<ViewModelBase, T>>>
		Ref<T> ViewModel()
		{
			QString name = T::staticMetaObject.className();

			auto it = m_registry.find(name);
			if (it != m_registry.end())
				return std::dynamic_pointer_cast<T>(it.value());

			Log::Warn(LogType::Editor, "'{}' could not been found in ViewModelRegistry.", name.toStdString());
			return nullptr;
		}

	private:
		QMap<QString, Ref<ViewModelBase>> m_registry;
	};
}
