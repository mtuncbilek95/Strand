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
	class SceneGraphTreeView : public QTreeView
	{
		Q_OBJECT
	public:
		SceneGraphTreeView(QWidget* pParent = nullptr);
		~SceneGraphTreeView();

	protected:
		void dragEnterEvent(QDragEnterEvent* pEvent) override;
		void dragMoveEvent(QDragMoveEvent* pEvent) override;
		void dragLeaveEvent(QDragLeaveEvent* pEvent) override;
		void dropEvent(QDropEvent* pEvent) override;
		void contextMenuEvent(QContextMenuEvent* pEvent) override;
		void keyPressEvent(QKeyEvent* pEvent) override;

	private:
		void startRenameForEntity(const QString& folderPath);

	private slots:
		void onCreateEntity(const QModelIndex& index);
		void onRemoveEntity(const QModelIndex& index);
		void onRenameEntity(const QModelIndex& index, const QString& newName);

		void onEditorCommitted(QWidget* pEditor);
		void onEditorClosed(QWidget* pEditor, QAbstractItemDelegate::EndEditHint hint);

	private:
		QString m_newItemName; // Used for renaming entities
	};
}
