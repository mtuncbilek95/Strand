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
	class DomainListView : public QListView
	{
		Q_OBJECT
	public:
		DomainListView(QWidget* pParent = nullptr);
		~DomainListView() override = default;

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
		QString m_newItemPath = {}; // Used for renaming
	};
}
