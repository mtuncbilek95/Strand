#include "DragFloatInput.h"

namespace Flax
{
	DragFloatInput::DragFloatInput(const QColor& color, f32 value, QWidget* pParent) : QWidget(pParent),
		m_value(value), m_mouseLastPos(QPoint(-1, -1))
	{
		setObjectName("Inspector_DragFloatInput");
		setFixedHeight(24);

		QHBoxLayout* layout = new QHBoxLayout(this);
		layout->setContentsMargins(0, 0, 0, 0);
		layout->setSpacing(0);

		// Color stripe
		m_colorLabel = new QLabel(this);
		m_colorLabel->setObjectName("Inspector_DragFloatInput_ColorLabel");
		m_colorLabel->setFixedWidth(4);
		m_colorLabel->setStyleSheet(QString("background-color: %1; border-top-left-radius: 6px; border-bottom-left-radius: 6px;")
			.arg(color.name()));
		layout->addWidget(m_colorLabel);

		// Draggable label
		m_dragLabel = new QLabel(QString::number(value, 'f', 4), this);
		m_dragLabel->setObjectName("Inspector_DragFloatInput_DragLabel");
		m_dragLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
		m_dragLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Preferred);
		m_dragLabel->setTextInteractionFlags(Qt::NoTextInteraction);
		m_dragLabel->setWordWrap(false);
		layout->addWidget(m_dragLabel, 1);

		m_textLabel = new QLineEdit(QString::number(value, 'f', 4), this);
		m_textLabel->setObjectName("Inspector_DragFloatInput_TextLabel");
		m_textLabel->setVisible(false);
		m_textLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Preferred);
		m_textLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
		m_textLabel->setContentsMargins(0, 0, 0, 0);
		layout->addWidget(m_textLabel, 1);

		connect(m_textLabel, &QLineEdit::editingFinished, this, &DragFloatInput::commitText);
	}

	DragFloatInput::~DragFloatInput()
	{
	}

	void DragFloatInput::mousePressEvent(QMouseEvent* event)
	{
		if (event->button() == Qt::LeftButton)
			m_mouseLastPos = event->globalPos();
	}

	void DragFloatInput::mouseMoveEvent(QMouseEvent* event)
	{
		if (m_mouseLastPos != QPoint(-1, -1))
		{
			QPoint delta = event->globalPos() - m_mouseLastPos;
			m_mouseLastPos = event->globalPos();
			m_value += delta.x() * 0.1;
			updateDisplay();
		}
	}

	void DragFloatInput::mouseReleaseEvent(QMouseEvent* event)
	{
		m_mouseLastPos = QPoint(-1, -1);
	}

	void DragFloatInput::mouseDoubleClickEvent(QMouseEvent* event)
	{
		m_dragLabel->setVisible(false);
		m_textLabel->setVisible(true);
		m_textLabel->setFocus();
	}

	void DragFloatInput::commitText()
	{
		b8 ok;
		f32 newValue = m_textLabel->text().toFloat(&ok);
		if (ok) {
			m_value = newValue;
		}
		m_textLabel->setVisible(false);
		m_dragLabel->setVisible(true);
		updateDisplay();
	}

	void DragFloatInput::updateDisplay()
	{
		m_dragLabel->setText(QString::number(m_value, 'f', 4));
		m_textLabel->setText(QString::number(m_value, 'f', 4));
	}
}
