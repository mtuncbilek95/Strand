#include "Vector3Widget.h"

#include <Editor/InspectorWidget/DragFloatInput/DragFloatInput.h>

namespace Flax
{
	Vector3Widget::Vector3Widget(QWidget* pParent) : QWidget(pParent)
	{
		QHBoxLayout* layout = new QHBoxLayout(this);
		layout->setSpacing(4);
		layout->setContentsMargins(0, 0, 0, 0);

		mXInput = new DragFloatInput(QColor("#ff4c4c"), 0.0f, this);
		mYInput = new DragFloatInput(QColor("#4cff4c"), 0.0f, this);
		mZInput = new DragFloatInput(QColor("#4c4cff"), 0.0f, this);

		layout->addWidget(mXInput);
		layout->addWidget(mYInput);
		layout->addWidget(mZInput);
	}

	Vector3Widget::~Vector3Widget()
	{
	}
}
