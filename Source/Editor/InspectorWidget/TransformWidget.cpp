#include "TransformWidget.h"

#include <Editor/InspectorWidget/VectorWidget/Vector3Widget.h>

namespace Flax
{
	TransformWidget::TransformWidget(QWidget* pParent) : QWidget(pParent)
	{
		QVBoxLayout* layout = new QVBoxLayout(this);

		m_position = new Vector3Widget(this);
		m_rotation = new Vector3Widget(this);
		m_scale = new Vector3Widget(this);

		layout->addWidget(m_position);
		layout->addWidget(m_rotation);
		layout->addWidget(m_scale);
	}

	TransformWidget::~TransformWidget()
	{
	}
}
