#include "CustomPBV.h"

#include <Runtime/FileSystem/Service/VirtualFileService.h>
#include <Editor/ProjectBrowser/Model/ProjectBrowserRole.h>
#include <Editor/ProjectBrowser/Model/ProjectBrowserModel.h>

namespace Flax
{
	CustomPBV::CustomPBV(QWidget* pParent) : QListView(pParent)
	{
		//setSelectionMode(QAbstractItemView::SingleSelection);
		//setEditTriggers(QAbstractItemView::NoEditTriggers);
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
	}

	CustomPBV::~CustomPBV()
	{
	}

	void CustomPBV::dragEnterEvent(QDragEnterEvent* pEvent)
	{
		if (pEvent->mimeData()->hasUrls())
			pEvent->acceptProposedAction();
		else
			pEvent->ignore();
	}

	void CustomPBV::dragMoveEvent(QDragMoveEvent* pEvent)
	{
		if (pEvent->mimeData()->hasUrls())
			pEvent->acceptProposedAction();
		else
			pEvent->ignore();
	}

	void CustomPBV::dragLeaveEvent(QDragLeaveEvent* pEvent)
	{
		QListView::dragLeaveEvent(pEvent);
	}

	void CustomPBV::dropEvent(QDropEvent* pEvent)
	{
		QPoint dropPos = pEvent->pos();

		QModelIndex targetIndex = indexAt(dropPos);
		QModelIndex parentIndex = targetIndex.parent();
		QString targetPath;

		// If targetIndex is valid, object dropped on something. If not, it dropped to the rootIndex().
		if (!targetIndex.isValid())
			targetIndex = rootIndex();

		targetPath = targetIndex.data(i32(ProjectBrowserRole::ObjectPath)).toString();
		if (!targetIndex.isValid())
		{
			targetPath = "Assets";
			parentIndex = QModelIndex();
		}

		pEvent->acceptProposedAction();

		Path srcPath = pEvent->mimeData()->urls()[0].toLocalFile().toStdString();
		auto vfm = RuntimeService::Get<VirtualFileService>();
		
		// TODO: Temporarily testing purpose
		vfm->ExternalCopy(srcPath, Path(targetPath.toStdString()));
		static_cast<ProjectBrowserModel*>(model())->ResetModel(targetIndex);
	}

	void CustomPBV::startDrag(Qt::DropActions supportedActions)
	{
		QListView::startDrag(supportedActions);
	}
}
