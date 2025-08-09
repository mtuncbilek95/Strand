/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Data/Definitions/StdNames.h>
#include <Runtime/Logger/Logger.h>
#include <Editor/Data/Controller/ControllerBase.h>

namespace Strand
{
	class ControllerManager
	{
	public:
		template<typename T, typename = std::enable_if<std::is_base_of<ControllerBase, T>::value>>
		static void RegisterController()
		{
			QString name = T::staticMetaObject.className();
			if (Controllers().contains(name))
			{
				Log::Warn(LogType::Editor, "Controller of type '{}' is already registered.", name.toStdString());
				return;
			}
			Controllers().insert(name, new T());
		}

		template<typename T, typename = std::enable_if<std::is_base_of<ControllerBase, T>::value>>
		static T* Get()
		{
			QString name = T::staticMetaObject.className();
			if (!Controllers().contains(name))
				RegisterController<T>();

			return static_cast<T*>(Controllers()[name]);
		}

	private:
		static QHash<QString, ControllerBase*>& Controllers()
		{
			static QHash<QString, ControllerBase*> controllers;
			return controllers;
		}
	};
}
