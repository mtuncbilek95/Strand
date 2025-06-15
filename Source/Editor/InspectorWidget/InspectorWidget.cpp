#include "InspectorWidget.h"

#include <Editor/InspectorWidget/ViewWidget/TransformWidget.h>

namespace Flax
{
	InspectorWidget::InspectorWidget(QWidget* pParent) : QWidget(pParent)
	{
		setObjectName("Scene_HierarchyWidget");
		setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		setContentsMargins(0, 0, 0, 0);

		m_componentList = new QListWidget(this);
		m_componentList->setSpacing(4);
		m_componentList->setFrameShape(QFrame::NoFrame);

		QVBoxLayout* layout = new QVBoxLayout(this);
		layout->addWidget(m_componentList);
		layout->setContentsMargins(0, 0, 0, 0);

		setLayout(layout);

		QListWidgetItem* item = new QListWidgetItem();
		TransformWidget* transformWidget = new TransformWidget();
		item->setSizeHint(transformWidget->sizeHint());

		m_componentList->addItem(item);
		m_componentList->setItemWidget(item, transformWidget);
	}

	InspectorWidget::~InspectorWidget()
	{
	}

	void InspectorWidget::showComponentsOf(const QModelIndex& index)
	{
	}
}
