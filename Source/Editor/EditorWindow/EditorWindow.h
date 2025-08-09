/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Editor/Core/CoreMinimal.h>

namespace Strand
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
