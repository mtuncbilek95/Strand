#include "SceneRendererView.h"

namespace Flax
{
	SceneRendererView::SceneRendererView(QWidget* pParent) : QWidget(pParent)
	{
		setContentsMargins(0, 0, 0, 0);
		setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

		QFrame* frame = new QFrame(this);
		frame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		frame->setStyleSheet("background: black;");

		QVBoxLayout* mainLayout = new QVBoxLayout(this);
		mainLayout->setAlignment(Qt::AlignCenter);
		mainLayout->addWidget(frame);

		setLayout(mainLayout);
	}

	SceneRendererView::~SceneRendererView()
	{
	}

	void SceneRendererView::resizeEvent(QResizeEvent* event)
	{
	}
}
