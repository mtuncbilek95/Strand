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
	class FileMenu : public QMenu
	{
		Q_OBJECT
	public:
		FileMenu(QWidget* pParent = nullptr);
		~FileMenu();

		void registerAction(const QString& actionName);
		void unregisterAction(const QString& actionName);

	signals:
		void onActionSignalled(const QString& actionName, QAction* pAction);

	private slots:
		void onActionTriggered(QAction* pAction);

	private:
		QHash<QString, QAction*> m_actions;
	};
}
