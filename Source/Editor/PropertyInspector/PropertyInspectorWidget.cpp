#include "PropertyInspectorWidget.h"

#include <Editor/PropertyInspector/PropertyInspectorListView.h>

namespace Strand
{
	PropertyInspectorWidget::PropertyInspectorWidget(QWidget* pParent) : QWidget(pParent)
	{
		setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		setContentsMargins(0, 0, 0, 0);

		QVBoxLayout* mainLayout = new QVBoxLayout(this);
		mainLayout->setContentsMargins(0, 0, 0, 0);
		mainLayout->setSpacing(0);

		m_propertyView = new PropertyInspectorListView(this);

		m_addComponentButton = new QPushButton("Add Component", this);
		m_addComponentButton->setFixedHeight(32);
		m_addComponentButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
		m_addComponentButton->setMinimumWidth(256);

		mainLayout->addWidget(m_propertyView);
		mainLayout->addWidget(m_addComponentButton);

		connect(m_addComponentButton, &QPushButton::clicked, this, &PropertyInspectorWidget::onAddComponentClicked);
	}

	void PropertyInspectorWidget::onAddComponentClicked()
	{
	}
}