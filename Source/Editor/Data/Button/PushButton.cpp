#include "PushButton.h"

namespace Flax
{
	PushButton::PushButton(QWidget* pParent) : QPushButton(pParent)
	{

	}

	PushButton::~PushButton()
	{
	}

	void PushButton::enterEvent(QEnterEvent* event)
	{
		setCursor(Qt::PointingHandCursor);

		QPushButton::enterEvent(event);
	}

	void PushButton::leaveEvent(QEvent* event)
	{
		unsetCursor();

		QPushButton::leaveEvent(event);
	}
}
