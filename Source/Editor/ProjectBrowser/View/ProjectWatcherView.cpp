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
		indexStack.prepend(QModelIndex());

		for (int i = 0; i < indexStack.size(); ++i)
		{
			const QModelIndex& idx = indexStack[i];

			QString label;
			if (!idx.isValid())
				label = "Assets";
			else
				label = idx.data(Qt::DisplayRole).toString();

			QPushButton* button = new QPushButton(label, this);
			button->setObjectName("ProjectWatcherView_Button");
			button->setFlat(true);
			button->setCursor(Qt::PointingHandCursor);

			QFontMetrics fmb(button->font());
			i32 labW = fmb.horizontalAdvance(label);
			button->setFixedWidth(labW + 2);

			connect(button, &QPushButton::clicked, this, [this, idx]() {
				emit onWatcherClicked(idx);
				});

			layout->addWidget(button);

			if (i != indexStack.size() - 1)
			{
				QLabel* separator = new QLabel(">", this);
				separator->setObjectName("ProjectWatcherView_Separator");
				separator->setAlignment(Qt::AlignCenter);
				separator->setContentsMargins(0, 0, 0, 0);

				layout->addWidget(separator);
			}
		}

		layout->addStretch();
	}
}
