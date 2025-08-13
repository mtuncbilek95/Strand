#include "PropertyInspectorListView.h"

#include <Runtime/SceneGraph/Components/TransformComponent.h>
#include <Editor/PropertyInspector/ReflectedComponentWidget.h>

namespace Strand
{
	PropertyInspectorListView::PropertyInspectorListView(QWidget* pParent) : QListWidget(pParent)
	{
		QListWidgetItem* item1 = new QListWidgetItem(this);
		IComponent* transform = new TransformComponent();

		ReflectedComponentWidget* transformWidget = new ReflectedComponentWidget(transform, this);

		item1->setSizeHint(transformWidget->sizeHint());
		
		insertItem(0, item1);
		setItemWidget(item1, transformWidget);

		setUniformItemSizes(true);
		setSpacing(0);
		setContentsMargins(0, 0, 0, 0);
		setSelectionMode(QAbstractItemView::ExtendedSelection);
		setEditTriggers(QAbstractItemView::EditKeyPressed |
			QAbstractItemView::SelectedClicked);
	}

	void PropertyInspectorListView::onEntitySelected(Entity* pEntity)
	{
	}

	void PropertyInspectorListView::onEntityDeselected(Entity* pEntity)
	{
	}

	void PropertyInspectorListView::resizeEvent(QResizeEvent* pEvent)
	{
		i32 minRequiredWidth = calculateMinimumWidth();
		if (pEvent->size().width() < minRequiredWidth)
		{
			resize(minRequiredWidth, height());
			return;
		}

		QListWidget::resizeEvent(pEvent);
	}

	void PropertyInspectorListView::mousePressEvent(QMouseEvent* pEvent)
	{
	}

	void PropertyInspectorListView::mouseReleaseEvent(QMouseEvent* pEvent)
	{
	}

	void PropertyInspectorListView::mouseMoveEvent(QMouseEvent* pEvent)
	{
	}

	void PropertyInspectorListView::keyPressEvent(QKeyEvent* pEvent)
	{
	}

	void PropertyInspectorListView::keyReleaseEvent(QKeyEvent* pEvent)
	{
	}

	void PropertyInspectorListView::wheelEvent(QWheelEvent* pEvent)
	{
	}

	void PropertyInspectorListView::contextMenuEvent(QContextMenuEvent* pEvent)
	{
	}

	void PropertyInspectorListView::createComponentWidgets()
	{
	}

	void PropertyInspectorListView::clearComponentWidgets()
	{
	}

	i32 PropertyInspectorListView::calculateMinimumWidth() const
	{
		i32 maxMin = 0;
		for(i32 i = 0; i < count(); ++i)
		{
			QWidget* widget = itemWidget(item(i));
			if (widget)
				maxMin = qMax(maxMin, widget->minimumWidth());
		}

		return maxMin + 20;
	}
}