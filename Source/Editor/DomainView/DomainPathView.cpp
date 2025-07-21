#include "DomainPathView.h"

namespace Flax
{
	DomainPathView::DomainPathView(QWidget* pParent) : QWidget(pParent)
	{
		setObjectName("DomainPathView_Widget");

		QHBoxLayout* mainLayout = new QHBoxLayout(this);
		mainLayout->setContentsMargins(0, 2, 0, 2);
		mainLayout->setSpacing(2);
		mainLayout->setAlignment(Qt::AlignLeft);
	}

	DomainPathView::~DomainPathView()
	{
	}

	void DomainPathView::refreshPathView(const QString& path)
	{
		auto vfm = RuntimeService::Get<VirtualFileService>();
		Path virtualPath = vfm->VirtualPath(path.toStdString());

		Vector<QString> segments;
		for (const auto& segment : virtualPath)
			segments.emplace_back(QString::fromStdString(segment.string()));

		clearLayout();

		QHBoxLayout* mainLayout = qobject_cast<QHBoxLayout*>(layout());
		for (usize i = 0; i < segments.size(); i++)
		{
			QPushButton* button = new QPushButton(segments[i], this);
			button->setFlat(true);
			button->setObjectName("DomainPathView_Button");
			button->setCursor(Qt::PointingHandCursor);

			QFontMetrics fm(button->font());
			i32 btnWidth = fm.horizontalAdvance(segments[i]) + 32;
			button->setFixedWidth(btnWidth);

			Path currentPath = vfm->AbsolutePath(virtualPath).lexically_normal();
			while (!currentPath.empty() && currentPath != currentPath.root_path())
			{
				if (currentPath.filename() == segments[i].toStdString())
					break;
				currentPath = currentPath.parent_path();
			}

			connect(button, &QPushButton::clicked, this, [this, currentPath]()
				{
					emit onPathViewClicked(QString::fromStdString(currentPath.string()));
				});

			mainLayout->addWidget(button);

			if (i < segments.size() - 1)
			{
				QLabel* separator = new QLabel("/", this);
				separator->setObjectName("DomainPathView_Separator");
				mainLayout->addWidget(separator);
			}
		}
	}

	void DomainPathView::clearLayout()
	{
		QHBoxLayout* mainLayout = qobject_cast<QHBoxLayout*>(layout());

		while (QLayoutItem* item = mainLayout->takeAt(0))
		{
			if (QWidget* widget = item->widget())
				widget->deleteLater();
			delete item;
		}
	}
}
