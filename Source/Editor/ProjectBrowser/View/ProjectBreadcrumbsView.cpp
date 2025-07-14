#include "ProjectBreadcrumbsView.h"

namespace Flax
{
	ProjectBreadcrumbsView::ProjectBreadcrumbsView(QWidget* pParent) : QWidget(pParent)
	{
		m_layout = new QHBoxLayout(this);
		m_layout->setContentsMargins(4, 0, 4, 0);
		m_layout->setSpacing(2);
		m_layout->setAlignment(Qt::AlignVCenter);
		setLayout(m_layout);
	}

	ProjectBreadcrumbsView::~ProjectBreadcrumbsView()
	{
	}

	void ProjectBreadcrumbsView::rebuildBreadcrumbs(const QModelIndex& index)
	{
		QHBoxLayout* layout = qobject_cast<QHBoxLayout*>(this->layout());

		while (QLayoutItem* item = layout->takeAt(0))
		{
			if (QWidget* widget = item->widget())
				widget->deleteLater();
			delete item;
		}

		// Build QModelIndex list from root to current
		QList<QModelIndex> indexStack;
		QModelIndex idx = index;
		while (idx.isValid())
		{
			indexStack.prepend(idx);
			idx = idx.parent();
		}

		for (int i = 0; i < indexStack.size(); ++i)
		{
			const QModelIndex& idx = indexStack[i];
			QString label = idx.data(Qt::DisplayRole).toString();

			QPushButton* button = new QPushButton(label, this);
			button->setFlat(true);
			button->setCursor(Qt::PointingHandCursor);

			/*connect(button, &QPushButton::clicked, this, [this, idx]() {
				emit onWatcherClicked(idx);
				});*/

			layout->addWidget(button);

			if (i != indexStack.size() - 1)
			{
				QLabel* separator = new QLabel(">", this);
				layout->addWidget(separator);
			}
		}

		layout->addStretch();
	}
}
