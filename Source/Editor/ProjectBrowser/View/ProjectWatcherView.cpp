#include "ProjectWatcherView.h"

#include <Runtime/FileSystem/Service/VirtualFileService.h>
#include <Editor/ProjectBrowser/Model/ProjectBrowserFilterProxy.h>
#include <Editor/ProjectBrowser/ViewModel/ProjectBrowserViewModel.h>

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

		m_fsModel = ViewModelRegistry::Get().ViewModel<ProjectBrowserViewModel>()->Model();
		m_proxy = ViewModelRegistry::Get().ViewModel<ProjectBrowserViewModel>()->Proxy();
		m_mountPoint = RuntimeService::Get<VirtualFileService>()->AbsolutePath("Assets");
	}

	ProjectWatcherView::~ProjectWatcherView()
	{
	}

	void ProjectWatcherView::rebuildWatcher(const QModelIndex& index)
	{
		if (!index.isValid())
			return;

		QModelIndex modelIndex = m_proxy->mapToSource(index);

		QString currentRoute = m_fsModel->fileInfo(modelIndex).absoluteFilePath(); // Temporary placeholder
		Path currentPath = Path(currentRoute.toStdString());

		Vector<QString> segments;
		for (const auto& segment : currentPath)
			segments.emplace_back(QString::fromStdString(segment.string()));

		clearLayout();

		// Find the segment start point. Loop has to start from the end path of mountPoint
		i32 segmentStart = 0;

		Vector<QString> mountSegments;
		for (const auto& segment : m_mountPoint)
			mountSegments.emplace_back(QString::fromStdString(segment.string()));

		for (i32 i = segments.size() - 1; i >= 0; i--)
		{
			if (segments[i] == mountSegments[mountSegments.size() - 1])
			{
				segmentStart = i;
				break;
			}
		}

		for (usize i = segmentStart; i < segments.size(); i++)
		{
			QPushButton* button = new QPushButton(segments[i], this);
			button->setObjectName("ProjectWatcherView_Button");
			button->setFlat(true);
			button->setCursor(Qt::PointingHandCursor);

			QFontMetrics fontMetrics(button->font());
			button->setMinimumWidth(fontMetrics.horizontalAdvance(segments[i]) + 20);
			button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
			button->setContentsMargins(0, 0, 0, 0);

			connect(button, &QPushButton::clicked, this, [this, modelIndex, i, segments]()
				{
					QModelIndex newIndex = modelIndex;
					for (i32 j = 0; j < segments.size() - i - 1; j++)
						newIndex = newIndex.parent();
					newIndex = m_proxy->mapFromSource(newIndex);
					emit onWatcherClicked(newIndex);
				});

			m_layout->addWidget(button);

			if (i != segments.size() - 1)
			{
				QLabel* separator = new QLabel(">", this);
				separator->setObjectName("ProjectWatcherView_Separator");
				separator->setAlignment(Qt::AlignCenter);
				separator->setContentsMargins(0, 0, 0, 0);

				m_layout->addWidget(separator);
			}
		}

		m_layout->addStretch();
	}

	void ProjectWatcherView::clearLayout()
	{
		while (QLayoutItem* item = m_layout->takeAt(0))
		{
			if (QWidget* widget = item->widget())
				widget->deleteLater();
			delete item;
		}
	}
}
