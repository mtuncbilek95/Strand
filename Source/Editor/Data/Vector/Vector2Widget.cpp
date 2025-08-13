#include "Vector2Widget.h"

namespace Strand
{
	Vector2Widget::Vector2Widget(const QString& name, QWidget* pParent) : QWidget(pParent)
	{
		QHBoxLayout* mainLayout = new QHBoxLayout(this);
		mainLayout->setContentsMargins(8, 4, 8, 4);
		mainLayout->setSpacing(4);
		mainLayout->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

		m_nameLabel = new QLabel(name, this);
		m_nameLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
		m_nameLabel->setStyleSheet("font-weight: bold; font-size: 12px; padding: 2px;");

		m_xSlider = new ValueWidget("X", NumberValueType::FloatingPoint, this);
		m_ySlider = new ValueWidget("Y", NumberValueType::FloatingPoint, this);

		QHBoxLayout* sliderLayout = new QHBoxLayout();
		sliderLayout->setContentsMargins(0, 0, 0, 0);
		sliderLayout->setSpacing(4);
		sliderLayout->addWidget(m_xSlider);
		sliderLayout->addWidget(m_ySlider);
		sliderLayout->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

		mainLayout->addWidget(m_nameLabel);
		mainLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
		mainLayout->addLayout(sliderLayout);
	}
}