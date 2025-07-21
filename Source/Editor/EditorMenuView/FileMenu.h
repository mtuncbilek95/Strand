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
