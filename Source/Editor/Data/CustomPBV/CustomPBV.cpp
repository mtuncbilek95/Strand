#include "CustomPBV.h"

#include <Runtime/FileSystem/Service/VirtualFileService.h>

namespace Flax
{
	CustomPBV::CustomPBV(QWidget* pParent) : QListView(pParent)
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
	}

	void CustomPBV::startDrag(Qt::DropActions supportedActions)
	{
		QListView::startDrag(supportedActions);
	}
}
