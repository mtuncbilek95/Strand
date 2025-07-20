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
	class ProjectListView : public QListView
	{
		Q_OBJECT
	public:
		ProjectListView(QWidget* pParent = nullptr);
		~ProjectListView();

	signals:
		void onCreateFolder(const QModelIndex& index);

	private slots:
		void onShowContextMenu(const QPoint& pos);

	protected:
		void dragEnterEvent(QDragEnterEvent* pEvent) override;
		void dragMoveEvent(QDragMoveEvent* pEvent) override;
		void dragLeaveEvent(QDragLeaveEvent* pEvent) override;
		void dropEvent(QDropEvent* pEvent) override;
		void mousePressEvent(QMouseEvent* pEvent) override;
		
	};
}
