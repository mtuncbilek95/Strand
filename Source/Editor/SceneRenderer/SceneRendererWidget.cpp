#include "SceneRendererWidget.h"

#include <Editor/SceneRenderer/SceneRendererView.h>
#include <Editor/SceneRenderer/SceneToolView.h>

namespace Strand
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

	void SceneRendererWidget::onClickedPlay()
	{
		EDITOR_NOT_IMPLEMENTED_YET(void());
	}

	void SceneRendererWidget::onClickedPause()
	{
		EDITOR_NOT_IMPLEMENTED_YET(void());
	}

	void SceneRendererWidget::onClickedStop()
	{
		EDITOR_NOT_IMPLEMENTED_YET(void());
	}

	void SceneRendererWidget::setupSignals()
	{
		connect(m_toolView, &SceneToolView::onPlaySignaled, this, &SceneRendererWidget::onClickedPlay);
		connect(m_toolView, &SceneToolView::onPauseSignaled, this, &SceneRendererWidget::onClickedPause);
		connect(m_toolView, &SceneToolView::onStopSignaled, this, &SceneRendererWidget::onClickedStop);
	}
}


