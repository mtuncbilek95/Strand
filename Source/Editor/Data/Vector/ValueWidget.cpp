#include "ValueWidget.h"

namespace Strand
{
	ValueWidget::ValueWidget(const QString& name, NumberValueType type, QWidget* pParent) : QWidget(pParent),
		m_isDragging(false), m_dragStartPosition(QPoint(0, 0))
	{
		QHBoxLayout* mainLayout = new QHBoxLayout(this);
		mainLayout->setContentsMargins(0, 0, 0, 0);
		mainLayout->setSpacing(0);

		m_nameLabel = new QLabel(name.isEmpty() ? "↕" : name + ":", this);

		m_value = new QDoubleSpinBox(this);
		m_value->setButtonSymbols(QAbstractSpinBox::NoButtons);
		m_value->setRange(-std::numeric_limits<f64>::max(), std::numeric_limits<f64>::max());
		m_value->setDecimals(type == NumberValueType::Integer ? 0 : 3);
		m_value->setSingleStep(0.1);
		m_value->setFixedWidth(48);

		mainLayout->addWidget(m_nameLabel);
		mainLayout->addWidget(m_value);
	}

	void ValueWidget::mousePressEvent(QMouseEvent* event)
	{
		QWidget* childWidget = childAt(event->pos());
		if (childWidget == m_nameLabel)
		{
			m_isDragging = true;
			m_dragStartPosition = event->pos();
			setCursor(Qt::SizeHorCursor);
		}

		QWidget::mousePressEvent(event);
	}

	void ValueWidget::mouseReleaseEvent(QMouseEvent* event)
	{
		if (m_isDragging)
		{
			m_isDragging = false;
			setCursor(Qt::ArrowCursor);
		}

		QWidget::mouseReleaseEvent(event);
	}

	void ValueWidget::mouseMoveEvent(QMouseEvent* event)
	{
		if (m_isDragging)
		{
			QPoint currentPos = event->pos();
			QPoint delta = currentPos - m_dragStartPosition;

			i32 stepSize = 5;
			if (abs(delta.x()) >= stepSize)
			{
				i32 steps = delta.x() / stepSize;

				f64 singleStep = m_value->singleStep();
				f64 newValue = m_value->value() + (steps * singleStep);

				newValue = qBound(m_value->minimum(), newValue, m_value->maximum());
				m_value->setValue(newValue);

				m_dragStartPosition = currentPos;
			}
		}
		else
		{
			QWidget* childWidget = childAt(event->pos());
			if (childWidget == m_nameLabel)
				setCursor(Qt::OpenHandCursor);
		}

		QWidget::mouseMoveEvent(event);
	}
}