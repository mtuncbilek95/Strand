#include "ProjectWatcherView.h"

namespace Flax
{
	ProjectWatcherView::ProjectWatcherView(QWidget* pParent) : QWidget(pParent)
	{
		setObjectName("ProjectWatcherView_Widget");
		m_layout = new QHBoxLayout(this);
		m_layout->setContentsMargins(4, 0, 4, 0);
		m_layout->setSpacing(0);
		m_layout->setAlignment(Qt::AlignVCenter);
		setLayout(m_layout);
	}

	ProjectWatcherView::~ProjectWatcherView()
	{
	}

	void ProjectWatcherView::rebuildWatcher(const QModelIndex& index)
	{
	}
}
