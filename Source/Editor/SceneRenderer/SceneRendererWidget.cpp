#include "SceneRendererWidget.h"

#include <Editor/SceneRenderer/SceneRendererView.h>
#include <Editor/SceneRenderer/SceneToolView.h>

namespace Flax
{
	SceneRendererWidget::SceneRendererWidget(QWidget* pParent) : QWidget(pParent)
	{
		m_renderView = new SceneRendererView();
		m_toolView = new SceneToolView();

		QVBoxLayout* mainLayout = new QVBoxLayout(this);
		mainLayout->setContentsMargins(0, 0, 0, 0);
		mainLayout->setSpacing(0);

		mainLayout->addWidget(m_toolView);
		mainLayout->addWidget(m_renderView);
	}

	SceneRendererWidget::~SceneRendererWidget()
	{
	}

	void SceneRendererWidget::onClickedPlay()
	{
	}

	void SceneRendererWidget::onClickedPause()
	{
	}

	void SceneRendererWidget::onClickedStop()
	{
	}

	void SceneRendererWidget::setupSignals()
	{
		connect(m_toolView, &SceneToolView::onPlaySignaled, this, &SceneRendererWidget::onClickedPlay);
		connect(m_toolView, &SceneToolView::onPauseSignaled, this, &SceneRendererWidget::onClickedPause);
		connect(m_toolView, &SceneToolView::onStopSignaled, this, &SceneRendererWidget::onClickedStop);
	}
}


