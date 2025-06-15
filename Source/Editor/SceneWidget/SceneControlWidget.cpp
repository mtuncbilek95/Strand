#include "SceneControlWidget.h"

namespace Flax
{
	QSize iconButtonSize = QSize(32, 32);

	SceneControlWidget::SceneControlWidget(QWidget* pParent) : QWidget(pParent)
	{
		setObjectName("Scene_ControlWidget");
		setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

		m_playButton = new PushButton();
		m_playButton->setObjectName("Scene_ControlWidget_PlayButton");
		m_playButton->setFixedSize(iconButtonSize);
		m_playButton->setIconSize(2 * iconButtonSize / 3);
		m_playButton->setIcon(QIcon(R"(C:\Users\mtunc\Downloads\play.svg)"));

		m_pauseButton = new PushButton();
		m_pauseButton->setObjectName("Scene_ControlWidget_PauseButton");
		m_pauseButton->setFixedSize(iconButtonSize);
		m_pauseButton->setIconSize(2 * iconButtonSize / 3);
		m_pauseButton->setIcon(QIcon(R"(C:\Users\mtunc\Downloads\pause.svg)"));

		m_stopButton = new PushButton();
		m_stopButton->setObjectName("Scene_ControlWidget_StopButton");
		m_stopButton->setFixedSize(iconButtonSize);
		m_stopButton->setIconSize(2 * iconButtonSize / 3);
		m_stopButton->setIcon(QIcon(R"(C:\Users\mtunc\Downloads\stop.svg)"));

		QHBoxLayout* layout = new QHBoxLayout(this);
		layout->setContentsMargins(16, 0, 16, 0);
		layout->setSpacing(8);

		layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
		layout->addWidget(m_playButton);
		layout->addWidget(m_pauseButton);
		layout->addWidget(m_stopButton);
		layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
	}

	SceneControlWidget::~SceneControlWidget()
	{
	}
}