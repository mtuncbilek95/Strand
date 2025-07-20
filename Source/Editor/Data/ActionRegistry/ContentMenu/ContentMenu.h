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
	class ContentMenu : public QMenu
	{
		Q_OBJECT
	public:
		ContentMenu(QWidget* pParent = nullptr);
		~ContentMenu() override;

		void setModel(const QModelIndex& index) { m_modelIndex = index; }

	private slots:
		void onCreateFolder(b8 checked = false);

	private:
		HashMap<String, QAction*> m_actions;
		QModelIndex m_modelIndex;
	};
}
