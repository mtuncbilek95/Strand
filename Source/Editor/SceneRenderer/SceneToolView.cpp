#include "SceneToolView.h"

namespace Flax
{
	SceneToolView::SceneToolView(QWidget* pParent) : QWidget(pParent)
	{
		setObjectName("SceneToolView");
		setFixedHeight(40);
		setContentsMargins(0, 0, 0, 0);
		
		m_playButton = new QPushButton(this);
		m_playButton->setIcon(QIcon(":/Icons/SceneRenderer/PB_Play.svg"));
		m_playButton->setFixedSize(QSize(32, 32));
		m_playButton->setIconSize(QSize(24, 24));

		m_pauseButton = new QPushButton(this);
		m_pauseButton->setIcon(QIcon(":/Icons/SceneRenderer/PB_Pause.svg"));
		m_pauseButton->setFixedSize(QSize(32, 32));
		m_pauseButton->setIconSize(QSize(24, 24));

		m_stopButton = new QPushButton(this);
		m_stopButton->setIcon(QIcon(":/Icons/SceneRenderer/PB_Stop.svg"));
		m_stopButton->setFixedSize(QSize(32, 32));
		m_stopButton->setIconSize(QSize(24, 24));

		QHBoxLayout* layout = new QHBoxLayout(this);
		layout->setContentsMargins(0, 0, 0, 0);
		layout->setSpacing(8);
		
		layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
		layout->addWidget(m_playButton);
		layout->addWidget(m_pauseButton);
		layout->addWidget(m_stopButton);
		layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
	}
	
	SceneToolView::~SceneToolView()
	{
	}

	void SceneToolView::setupSignals()
	{
		connect(m_playButton, &QPushButton::clicked, this, &SceneToolView::onPlaySignaled);
		connect(m_pauseButton, &QPushButton::clicked, this, &SceneToolView::onPauseSignaled);
		connect(m_stopButton, &QPushButton::clicked, this, &SceneToolView::onStopSignaled);
	}
}
