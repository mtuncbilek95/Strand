#include "SceneGraphTreeView.h"

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
		QMenu contextMenu = QMenu(this);
		contextMenu.setAttribute(Qt::WA_DeleteOnClose);
		QModelIndex proxyIndex = indexAt(pEvent->pos());

		QAction* addEntt = contextMenu.addAction("Add Entity");
		QAction* removeEntt = nullptr;
		QAction* renameEntt = nullptr;
		QAction* duplicateEntt = nullptr;
		if (proxyIndex.isValid())
		{
			removeEntt = contextMenu.addAction("Remove Entity");
			renameEntt = contextMenu.addAction("Rename Entity");
			duplicateEntt = contextMenu.addAction("Duplicate Entity");
		}

		contextMenu.addSeparator();

		QMenu lightsMenu = QMenu("Lights", &contextMenu);

		lightsMenu.addAction("Add Sun");
		lightsMenu.addAction("Add Point-Light");
		lightsMenu.addAction("Add Area-Light");
		lightsMenu.addAction("Add Spot-Light");

		contextMenu.addMenu(&lightsMenu);

		QAction* selectedAction = contextMenu.exec(pEvent->globalPos());
	}
	
	void SceneGraphTreeView::keyPressEvent(QKeyEvent* pEvent)
	{
	}
	
	void SceneGraphTreeView::onCreateEntity(const QModelIndex& index)
	{
	}
	
	void SceneGraphTreeView::onRemoveEntity(const QModelIndex& index)
	{
	}
}
