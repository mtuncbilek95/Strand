#include "ComponentTabWidget.h"

namespace Strand
{
	ComponentTabWidget::ComponentTabWidget(const QString& name, QWidget* pParent) : QWidget(pParent)
	{
		QHBoxLayout* mainLayout = new QHBoxLayout(this);
		mainLayout->setContentsMargins(4, 0, 8, 0);
		mainLayout->setSpacing(0);

		m_nameLabel = new QLabel(name, this);

		m_nameLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
		m_nameLabel->setStyleSheet("font-weight: bold; font-size: 14px; padding: 4px;");

		m_enableCheckbox = new QCheckBox(this);
		m_enableCheckbox->setText("Enable");
		m_enableCheckbox->setChecked(true);
		m_enableCheckbox->setStyleSheet("font-size: 12px; padding: 2px;");
		m_enableCheckbox->setCursor(Qt::PointingHandCursor);
		m_enableCheckbox->setLayoutDirection(Qt::RightToLeft);

		mainLayout->addWidget(m_nameLabel);
		mainLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
		mainLayout->addWidget(m_enableCheckbox);
		mainLayout->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

		connect(m_enableCheckbox, &QCheckBox::stateChanged, this, &ComponentTabWidget::onComponentChecked);
	}

	void ComponentTabWidget::onComponentStateChanged(i32 state)
	{
		emit onComponentChecked(state == Qt::Checked);
	}
}