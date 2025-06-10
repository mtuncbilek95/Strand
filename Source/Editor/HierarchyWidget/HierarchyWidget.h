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
	class HierarchyItemModel;

	class HierarchyWidget : public QWidget
	{
		Q_OBJECT
	public:
		HierarchyWidget(QWidget* pParent = nullptr);
		~HierarchyWidget();

	protected:
		bool eventFilter(QObject* pWatched, QEvent* pEvent) override;

	private slots:
		void onItemSelected(const QModelIndex& index);
		void onContextMenuRequested(const QPoint& pos);
		void onItemDoubleClicked(const QModelIndex& index);

	private:
		QTreeView* m_view;
		HierarchyItemModel* m_model;
	};
}
