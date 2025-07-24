#include "SceneGraphTreeView.h"

#include <Editor/SceneGraph/SceneGraphModel.h>
#include <Editor/SceneGraph/SceneGraphRole.h>

namespace Flax
{
	SceneGraphTreeView::SceneGraphTreeView(QWidget* pParent) : QTreeView(pParent)
	{
		setObjectName("SceneGraphTreeView");
		setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		setAcceptDrops(true);
		setDragDropMode(QAbstractItemView::DragDrop);
		setDragEnabled(true);
		setAcceptDrops(true);
		setDropIndicatorShown(true);
		setDefaultDropAction(Qt::MoveAction);
	}

	SceneGraphTreeView::~SceneGraphTreeView()
	{
	}

	void SceneGraphTreeView::dragEnterEvent(QDragEnterEvent* pEvent)
	{
		for (const auto& url : pEvent->mimeData()->urls())
		{
			QFileInfo fInfo(url.toLocalFile());
			if (fInfo.completeSuffix() == "scene" || fInfo.completeSuffix() == ".prefab")
				pEvent->acceptProposedAction();
		}

		pEvent->ignore();
	}

	void SceneGraphTreeView::dragMoveEvent(QDragMoveEvent* pEvent)
	{
		QTreeView::dragMoveEvent(pEvent);
	}

	void SceneGraphTreeView::dragLeaveEvent(QDragLeaveEvent* pEvent)
	{
		QTreeView::dragLeaveEvent(pEvent);
	}

	void SceneGraphTreeView::dropEvent(QDropEvent* pEvent)
	{

	}

	void SceneGraphTreeView::contextMenuEvent(QContextMenuEvent* pEvent)
	{
		QMenu* contextMenu = new QMenu(this);
		contextMenu->setAttribute(Qt::WA_DeleteOnClose);
		QModelIndex proxyIndex = indexAt(pEvent->pos());

		QAction* addEntt = contextMenu->addAction("Add Entity");
		QAction* removeEntt = nullptr;
		QAction* renameEntt = nullptr;
		QAction* duplicateEntt = nullptr;
		if (proxyIndex.isValid())
		{
			removeEntt = contextMenu->addAction("Remove Entity");
			renameEntt = contextMenu->addAction("Rename Entity");
			duplicateEntt = contextMenu->addAction("Duplicate Entity");
		}

		contextMenu->addSeparator();

		QMenu lightsMenu = QMenu("Lights", contextMenu);

		lightsMenu.addAction("Add Sun");
		lightsMenu.addAction("Add Point-Light");
		lightsMenu.addAction("Add Area-Light");
		lightsMenu.addAction("Add Spot-Light");

		contextMenu->addMenu(&lightsMenu);

		QAction* selectedAction = contextMenu->exec(pEvent->globalPos());

		if (!selectedAction)
		{
			pEvent->ignore();
			return;
		}

		if (selectedAction == addEntt)
		{
			onCreateEntity(proxyIndex);
		}
		else if (selectedAction == removeEntt)
		{
			onRemoveEntity(proxyIndex);
		}
		else if (selectedAction == renameEntt)
		{
		}
		else if (selectedAction == duplicateEntt)
		{
		}
		else
			pEvent->ignore();
	}

	void SceneGraphTreeView::keyPressEvent(QKeyEvent* pEvent)
	{
	}

	void SceneGraphTreeView::startRenameForEntity(const QString& folderPath)
	{

	}

	void SceneGraphTreeView::onCreateEntity(const QModelIndex& index)
	{
		QModelIndex proxyIndex = index;
		if (!proxyIndex.isValid())
			proxyIndex = rootIndex();

		auto* sgModel = qobject_cast<SceneGraphModel*>(model());
		sgModel->addEntity(proxyIndex);
	}

	void SceneGraphTreeView::onRemoveEntity(const QModelIndex& index)
	{
		QModelIndex proxyIndex = index;
		if (!proxyIndex.isValid())
			proxyIndex = rootIndex();
		auto* sgModel = qobject_cast<SceneGraphModel*>(model());
		sgModel->removeEntity(proxyIndex);
	}

	void SceneGraphTreeView::onRenameEntity(const QModelIndex& index, const QString& newName)
	{
	}

	void SceneGraphTreeView::onEditorCommitted(QWidget* pEditor)
	{
		QLineEdit* lineEdit = qobject_cast<QLineEdit*>(pEditor);
		if (!lineEdit)
			return;
		QModelIndex index = currentIndex();
		if (!index.isValid())
			return;
		auto* sgModel = qobject_cast<SceneGraphModel*>(model());
		if (sgModel)
			sgModel->renameEntity(index, lineEdit->text());
	}

	void SceneGraphTreeView::onEditorClosed(QWidget* pEditor, QAbstractItemDelegate::EndEditHint hint)
	{
		QLineEdit* lineEdit = qobject_cast<QLineEdit*>(pEditor);
		if (!lineEdit)
			return;
		if (hint == QAbstractItemDelegate::RevertModelCache)
		{
			QModelIndex index = currentIndex();
			if (index.isValid())
			{
				auto* sgModel = qobject_cast<SceneGraphModel*>(model());
				if (sgModel)
					lineEdit->setText(sgModel->data(index, i32(SceneGraphRole::EntityName)).toString());
			}
		}
	}
}
