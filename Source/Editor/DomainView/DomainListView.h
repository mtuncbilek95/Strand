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
	class DomainListView : public QListView
	{
		Q_OBJECT
	public:
		DomainListView(QWidget* pParent = nullptr);
		~DomainListView();

	protected:
		void dragEnterEvent(QDragEnterEvent* pEvent) override;
		void dragMoveEvent(QDragMoveEvent* pEvent) override;
		void dragLeaveEvent(QDragLeaveEvent* pEvent) override;
		void dropEvent(QDropEvent* pEvent) override;
		void contextMenuEvent(QContextMenuEvent* pEvent) override;
		void keyPressEvent(QKeyEvent* pEvent) override;

	private:
		void startRenameForNewFolder(const Path& folderPath);

	private slots:
		void onCreateFolder(const QModelIndex& sourceIndex);
		void onEditorCommitted(QWidget* pEditor);
		void onEditorClosed(QWidget* pEditor, QAbstractItemDelegate::EndEditHint hint);

	private:
		QString m_newItemPath; // Used for renaming
	};
}
