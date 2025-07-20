#include "ProjectListView.h"

#include <Runtime/Resources/Assets/Service/AssetService.h>

#include <Editor/ProjectBrowser/Model/ProjectBrowserFilterProxy.h>
#include <Editor/Data/ActionRegistry/MenuActionRegistry.h>
#include <Editor/Data/ActionRegistry/ContentMenu/ContentMenu.h>

namespace Flax
{
	ProjectListView::ProjectListView(QWidget* pParent)
	{
		setViewMode(QListView::IconMode);
		setDragDropMode(QAbstractItemView::DragDrop);
		setDragEnabled(true);
		setAcceptDrops(true);
		setDropIndicatorShown(true);
		setDefaultDropAction(Qt::MoveAction);
		setUniformItemSizes(true);
		setIconSize(QSize(96, 96));
		setGridSize(QSize(128, 128));
		setSpacing(12);
		setResizeMode(QListView::Adjust);

		MenuActionRegistry::Get().RegisterMenu<ContentMenu>();
	}

	ProjectListView::~ProjectListView()
	{
	}

	void ProjectListView::onShowContextMenu(const QPoint& pos)
	{
		QPoint globalPos = mapToGlobal(pos);
		QModelIndex index = indexAt(pos);

		if (!index.isValid())
			index = rootIndex();

		ContentMenu* menu = MenuActionRegistry::Get().PopupMenu<ContentMenu>(globalPos);
		menu->setModel(index);
	}

	void ProjectListView::dragEnterEvent(QDragEnterEvent* pEvent)
	{
		if (pEvent->mimeData()->hasUrls())
			pEvent->acceptProposedAction();
		else
			pEvent->ignore();
	}

	void ProjectListView::dragMoveEvent(QDragMoveEvent* pEvent)
	{
		if (pEvent->mimeData()->hasUrls())
			pEvent->acceptProposedAction();
		else
			pEvent->ignore();
	}

	void ProjectListView::dragLeaveEvent(QDragLeaveEvent* pEvent)
	{
		QListView::dragLeaveEvent(pEvent);
	}

	void ProjectListView::dropEvent(QDropEvent* pEvent)
	{
		QModelIndex targetIndex = indexAt(pEvent->pos());

		if (!targetIndex.isValid())
			targetIndex = rootIndex();
		
		// Ignore event if there are multiple URLs or no URLs
		if (pEvent->mimeData()->urls().size() > 1 || !pEvent->mimeData()->hasUrls())
			pEvent->ignore();

		QUrl data = pEvent->mimeData()->urls()[0];
		QString dataPath = data.toLocalFile();

		ProjectBrowserFilterProxy* proxyModel = qobject_cast<ProjectBrowserFilterProxy*>(model());
		QFileSystemModel* fsModel = qobject_cast<QFileSystemModel*>(proxyModel->sourceModel());

		QModelIndex fsIndex = proxyModel->mapToSource(targetIndex);

		RuntimeService::Get<AssetService>()->ImportAsset(Path(dataPath.toStdString()), fsModel->filePath(fsIndex).toStdString());

		pEvent->acceptProposedAction();
	}

	void ProjectListView::mousePressEvent(QMouseEvent* pEvent)
	{
		if (pEvent->button() == Qt::RightButton)
			onShowContextMenu(pEvent->pos());
		else
			QListView::mousePressEvent(pEvent);
	}
}
