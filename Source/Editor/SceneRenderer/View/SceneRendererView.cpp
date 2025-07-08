#include "SceneRendererView.h"

namespace Flax
{
	SceneRendererView::SceneRendererView(QWidget* pParent) : QWidget(pParent)
	{
		setMinimumSize(640, 480);
		setContentsMargins(0, 0, 0, 0);
		setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

		QFrame* frame = new QFrame(this);
		frame->setStyleSheet("background-color: black;");

		QVBoxLayout* mainLayout = new QVBoxLayout(this);
		mainLayout->addWidget(frame);
	}

	SceneRendererView::~SceneRendererView()
	{
	}
}
