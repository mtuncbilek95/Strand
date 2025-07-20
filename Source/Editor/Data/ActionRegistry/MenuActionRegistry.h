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
	class MenuActionRegistry : public Singleton<MenuActionRegistry>
	{
	public:
		template<typename T, typename = std::enable_if_t<std::is_base_of_v<QMenu, T>>>
		T* PopupMenu(const QPoint& pos)
		{
			QString objName = T::staticMetaObject.className();
			if (!m_menus.contains(objName))
			{
				Log::Error(LogType::Editor, "Menu '{}' is not registered.", objName.toStdString());
				return nullptr;
			}
			QMenu* menu = m_menus.value(objName);
			menu->popup(pos);

			return qobject_cast<T*>(menu);
		}

		template<typename T, typename = std::enable_if_t<std::is_base_of_v<QMenu, T>>>
		void RegisterMenu()
		{
			QString objName = T::staticMetaObject.className();
			if (m_menus.contains(objName))
			{
				Log::Error(LogType::Editor, "Menu '{}' is already registered.", objName.toStdString());
				return;
			}
			QMenu* menu = new T();
			m_menus.insert(objName, menu);
		}

	private:
		QHash<QString, QMenu*> m_menus;
	};
}
