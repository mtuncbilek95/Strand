/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Editor/Core/CoreMinimal.h>

namespace Flax
{
	enum class TabDirection
	{
		Left,
		Right,
		Bottom,
		Top
	};

	class EditorWindow : public QMainWindow
	{
	public:
		EditorWindow(QWidget* pParent = nullptr);
		~EditorWindow();

		void addTabTo(TabDirection dir, QWidget* widget, const QString& titleName);
	private:
		QHash<TabDirection, QTabWidget*> m_tabWidgets;

		QMenuBar* m_topMenuBar;
	};
}
