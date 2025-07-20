/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Editor/Core/CoreMinimal.h>

namespace Flax
{
	class ProjectWatcherView : public QWidget
	{
		Q_OBJECT
	public:
		ProjectWatcherView(QWidget* pParent = nullptr);
		~ProjectWatcherView();

		void rebuildWatcher(const QModelIndex& index);

	signals:
		void onWatcherClicked(const QModelIndex& index);

	private:
		void clearLayout();

	private:
		QHBoxLayout* m_layout;
		QFileSystemModel* m_fsModel;
		QSortFilterProxyModel* m_proxy;

		Path m_mountPoint;
	};
}
